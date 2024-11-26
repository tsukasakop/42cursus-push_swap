#include "push_swap.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/errno.h>

void	raise_err(char *msg)
{
	if (!msg)
		msg = "Error";
	//TODO: Replace to ft_fprintf
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void	assert_null(void * p, void *to_del, void (*del)(void *))
{
	if (p)
		return;
	if (to_del && del)
		del(to_del);
	raise_err("Error: null ptr provided.");
}

void	assert_integer(char *s, void *to_del, void (*del)(void *))
{
	assert_null((void *)s, to_del, del);
	if(*s == '+' || *s == '-')
		s++;
	//TODO: Replace to ft_isdigit
	if(!isdigit(*s))
		raise_err("Error: no number provided.");
	while(isdigit(*s))
		s++;
	if (*s)
	{
		printf("s=%s ", s);
		raise_err("Error: invalid number provided.");
	}
}

t_stack *str2stack(char *s)
{
	t_stack *p;
	p = malloc(sizeof(t_stack));
	if(!p)
		return NULL;
	// TODO: Replace to ft_atoi
	p->val = atoi((const char *)s);
	p->prev = NULL;
	p->next = NULL;
	return p;
}

t_stack *int2stack(int i)
{
	t_stack *p;
	p = malloc(sizeof(t_stack));
	if(!p)
		return NULL;
	// TODO: Replace to ft_atoi
	p->val = i;
	p->prev = NULL;
	p->next = NULL;
	return p;
}

void	del_stack(void *ptr)
{
	t_stack *cur;
	t_stack *tmp;
	if(!ptr)
		return;
	t_stack *p;
	p = (t_stack *)ptr;
	cur = p->next;
	free(p);
	while(cur && cur != p)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}

void	del_status(void *ptr)
{
	t_state *p;
	if(!ptr)
		return;
	p = (t_state *)ptr;
	if(p->a)
		del_stack(p->a);
	if(p->b)
		del_stack(p->b);
	size_t i;
	i=0;
	while(i<N_ACTION)
		del_status(p->ch[i++]);
	free(p);
	return;
}

void	print_state(t_state *s)
{
	printf(".score = %d,\n", s->score);
	t_stack *i;
	i = s->a;
	printf(".a(%p) = ", i);
	if (i)
	{
		printf("%d, ", i->val);
		i = i->next;
		while(i != s->a)
		{
			printf("%d, ", i->val);
			i = i->next;
		}
	};
	i = s->b;
	printf("\n.b(%p) = ", i);
	if (i)
	{
		printf("%d, ", i->val);
		i = i->next;
		while(i != s->b)
		{
			printf("%d, ", i->val);
			i = i->next;
		}
	}
	printf("\n");
}

t_state *arg2state(int n, char **s)
{
	t_state *state;
	t_stack *cur;
	// TODO: Replace to ft_calloc
	state = (t_state *)calloc(sizeof(t_state), 1);
	assert_null((void *)state, NULL, NULL);
	state->a = str2stack(*s);
	assert_null((void *)state->a, state, del_status);
	cur = state->a;
	while(--n)
	{
		cur->next = str2stack(*++s);
		assert_null((void *)cur->next, state, del_status);
		cur->next->prev = cur;
		cur = cur->next;
	}
	cur->next = state->a;
	state->a->prev = cur;
	return state;	
}

t_game *init_game(int c, char** v)
{
	t_game *game;
	game = malloc(sizeof(t_game));
	assert_null((void *)game, NULL, NULL);
	game->cur = arg2state(c, v);
	game->set = NULL;
	return game;
}

void validate_arg(int c, char** v)
{
	if(c == 0)
		raise_err("Error: no number");
	while(c--)
		assert_integer(*v++, NULL, NULL);
	return;
}

t_stack *dup_stack(t_stack *s)
{
	t_stack *p;
	t_stack *cur_orig;
	t_stack *cur_dup;

	if(!s)
		return NULL;
	p = int2stack(s->val);
	if(!p)
		return NULL;
	cur_orig = s;
	cur_dup = p;
	while(cur_orig->next != s)
	{
		cur_dup->next = int2stack(cur_orig->next->val);
		if (!cur_dup->next)
		{
			del_stack(p);
			return NULL;
		}
		cur_dup->next->prev = cur_dup;
		cur_dup = cur_dup->next;
		cur_orig = cur_orig->next;
	}
	cur_dup->next = p;
	p->prev = cur_dup;
	return p;
}

t_state *dup_state(t_state *s)
{
	t_state *p;
	p = (t_state *)calloc(sizeof(t_state), 1);
	if (!p)
		return NULL;
	p->a = dup_stack(s->a);
	p->b = dup_stack(s->b);
	if ((s->a && !p->a) || (s->b && !p->b))
	{
		free(p->a);
		free(p->b);
		free(p);
		return NULL;
	}
	return p;
}

void	swap(t_stack **s)
{
	t_stack *cur;
	t_stack *last;

	if (!*s || !(*s)->next)
		return;
	cur = *s;
	last = (*s)->prev;

	cur->prev = cur->next;
	cur->next = cur->prev->next;
	cur->next->prev = cur;
	cur = cur->prev;
	cur->next = cur->prev;
	cur->prev = last;
	last->next = cur;
	*s = cur;
}

void	push(t_stack **lhs, t_stack **rhs)
{
	t_stack *tmp;
	if (!*lhs)
		return;
	tmp = *lhs;
	if (*lhs == (*lhs)->next)
		*lhs = NULL;	
	else
	{
		*lhs = tmp->next;
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
	}
	if(!*rhs)
	{
		*rhs = tmp;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	else
	{
		tmp->next = *rhs;
		tmp->prev = (*rhs)->prev;
		tmp->next->prev = tmp;
		tmp->prev->next = tmp;
		*rhs = tmp;
	}
}

void	rotate(t_stack **s)
{
	if (!*s)
		return;
	*s = (*s)->next;
}

void	r_rotate(t_stack **s)
{
	if (!*s)
		return;
	*s = (*s)->prev;
}

void	sa(t_state *s)
{
	swap(&s->a);
}

void	sb(t_state *s)
{
	swap(&s->b);
}

void	ss(t_state *s)
{
	sa(s);
	sb(s);
}

void	pa(t_state *s)
{
	push(&s->a, &s->b);
}

void	pb(t_state *s)
{
	push(&s->b, &s->a);
}

void	ra(t_state *s)
{
	rotate(&s->a);
}

void	rb(t_state *s)
{
	rotate(&s->b);
}

void	rr(t_state *s)
{
	ra(s);
	rb(s);
}

void	rra(t_state *s)
{
	r_rotate(&s->a);
}

void	rrb(t_state *s)
{
	r_rotate(&s->b);
}

void	rrr(t_state *s)
{
	rra(s);
	rrb(s);
}

t_state *get_state(t_state *s, t_action a)
{
	t_state *ch;
	ch = dup_state(s);
	if (!ch)
		return NULL;
	void (*act[N_ACTION])(t_state *);
	act[SA] = sa;
	act[SB] = sb;
	act[SS] = ss;
	act[PA] = pa;
	act[PB] = pb;
	act[RA] = ra;
	act[RB] = rb;
	act[RR] = rr;
	act[RRA] = rra;
	act[RRB] = rrb;
	act[RRR] = rrr;
	act[a](s);
	return ch;
}

bool	emulate_action(t_state *s, int gen)
{
	t_action	i;

	//printf("gen: %d\n", gen);
	if (gen < 1)
		return true;
	i = SA;
	while(i < N_ACTION)
	{
		if(!s->ch[i])
		{
			s->ch[i] = get_state(s, i);
			if (!s->ch[i])
				return false;
		}
		i++;
	}
	i = SA;
	while(i < N_ACTION)
	{
		if (!emulate_action(s->ch[i], gen-1))
			return false;
		i++;
	}
	return true;
}

void del_game(void *ptr)
{
	if(!ptr)
		return;
	t_game *p;
	p = (t_game *)ptr;
	del_status((void *)p->cur);
	free(p);
}

void	run_game(t_game *g, int gen)
{
	if (!emulate_action(g->cur, gen))
	{
		del_game(g);
		raise_err("Error: emulate failed");
	}
}

int main(int argc, char** argv)
{
	t_game *g;

	printf("argc=%d\n", argc);
	validate_arg(argc-1, argv+1);
	g = init_game(argc-1, argv+1);
	run_game(g, 3);
	del_game(g);
}

void	test_state(t_game *g)
{
	print_state(g->cur);
	pa(g->cur);
	print_state(g->cur);
	pa(g->cur);
	print_state(g->cur);
	pa(g->cur);
	print_state(g->cur);
	pa(g->cur);
	print_state(g->cur);
	pb(g->cur);
	print_state(g->cur);
	sa(g->cur);
	print_state(g->cur);
	sb(g->cur);
	print_state(g->cur);
	ss(g->cur);
	print_state(g->cur);
	ra(g->cur);
	print_state(g->cur);
	rb(g->cur);
	print_state(g->cur);
	rr(g->cur);
	print_state(g->cur);
	rra(g->cur);
	print_state(g->cur);
	rrb(g->cur);
	print_state(g->cur);
	rrr(g->cur);
	print_state(g->cur);
}	
