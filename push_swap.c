#include "push_swap.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/errno.h>
#include <limits.h>

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
//	printf("%d", i);

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

void	del_state(void *ptr)
{
	t_state *p;
	if(!ptr)
		return;
	p = (t_state *)ptr;
	if(p->a)
		del_stack(p->a);
	if(p->b)
		del_stack(p->b);
	free(p);
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
}

bool	equal_stack(t_stack *lhs, t_stack *rhs)
{
	t_stack *cur_l;
	t_stack *cur_r;

	cur_l = lhs;
	cur_r = rhs;
	if(!cur_l || !cur_r)
		return cur_l == cur_r;
	if(cur_l->val != cur_r->val)
		return false;
	while(cur_l != lhs || cur_r != rhs)
	{
		if(cur_l->val != cur_r->val)
			return false;
		cur_l = cur_l->next;
		cur_r = cur_r->next;
	}
	return (cur_l == lhs && cur_r == rhs);
}

bool	equal_state(t_state *lhs, t_state *rhs)
{
	return equal_stack(lhs->a, rhs->a) && equal_stack(lhs->b, rhs->b);
}

void	print_status(t_state *s, int nest)
{
	t_action i; i =SA;
	int n;
	n=nest;
	while(n--)
		printf("\t");
	printf("%p\n", s);
	if(!s)
		return;
	while(i < N_ACTION)
	{
		if(s->ch[i])
			print_status(s->ch[i], nest+1);
		i++;
	}	
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
	state->score = get_score(state);
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
	//print_state(s);
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
	//print_state(p);
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

int count_slope(t_stack *s)
{
	if (!s)
		return 0;
	bool	is_increase;
	t_stack *cur; cur = s;
	int cnt = 1;
	is_increase = cur->next->val > cur->val;
	cur = cur->next;
	while(cur->next != s)
	{
		if(is_increase ^ (cur->next->val > cur->val))
		{
			is_increase = cur->next->val > cur->val;
			cnt++;
		}
		cur = cur->next;
	}
	return cnt;
}

int	get_score(t_state *s)
{
	if(s->score)
		return s->score;
	int sa;sa = count_slope(s->a);
	int sb;sb = count_slope(s->b);
	if(sa == 1 && sb == 0)
		return 0;
	return sa+sb;
}

int min_int(int lhs, int rhs)
{
	if(lhs < rhs)
		return lhs;
	else
		return rhs;
}

int get_best_score(t_state *s)
{
	int score;
	t_action i;
	if (s->score == 0)
		return 0;
	i = SA;
	score = INT_MAX;
	while(i < N_ACTION)
	{
		if (s->ch[i])
			score = min_int(score, get_best_score(s->ch[i]) + 1);
		i++;
	}
	return min_int(score, s->score << 4);
}

t_action	get_best_action(t_state *s)
{
	t_action cur;
	t_action best;
	int best_score;
	int	cur_score;
	best_score = INT_MAX;
	cur = SA;
	while(cur < N_ACTION)
	{
		if(s->ch[cur])
		{
			cur_score = get_best_score(s->ch[cur]);
			if(cur_score < best_score)
			{
				best_score = cur_score;
				best = cur;
			}
		}
		cur++;
	}
	return best;
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
	act[a](ch);
	if(equal_state(s, ch))
	{
		del_status(ch);
		return NULL;
	}
	ch->score = get_score(ch);
	return ch;
}

bool	emulate_action(t_state *s, int gen)
{
	t_action	i;

	if (gen < 1)
		return true;
	i = SA;
	while(i < N_ACTION)
	{
		if(!s->ch[i])
			s->ch[i] = get_state(s, i);
		i++;
	}
	i = SA;
	while(i < N_ACTION)
	{
		if (s->ch[i] && !emulate_action(s->ch[i], gen-1))
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

void	print_action(t_action a)
{
	char *names[N_ACTION];
	names[SA] = "sa";
	names[SB] = "sb";
	names[SS] = "ss";
	names[PA] = "pa";
	names[PB] = "pb";
	names[RA] = "ra";
	names[RB] = "rb";
	names[RR] = "rr";
	names[RRA] = "rra";
	names[RRB] = "rrb";
	names[RRR] = "rrr";
	printf("%s\n", names[a]);
}

void	proceed_state(t_state **s, t_action a)
{
	t_action cur;
	cur = SA;
	while(cur < N_ACTION)
	{
		if(cur != a)
			del_status((*s)->ch[cur]);
		cur++;
	}
	t_state *prev; prev = *s;
	*s = (*s)->ch[a];
	print_action(a);
	print_state(*s);
	del_state(prev);
}
	
void	run_game(t_game *g, int gen)
{
	while(g->cur->score)
	{
		if (!emulate_action(g->cur, gen))
		{
			del_game(g);
			raise_err("Error: emulate failed");
		}
		//print_status(g->cur, 0);
		t_action a; a=get_best_action(g->cur);
		proceed_state(&(g->cur), a);
	}
}

int main(int argc, char** argv)
{
	t_game *g;

	validate_arg(argc-1, argv+1);
	g = init_game(argc-1, argv+1);
	run_game(g, N_STEPS_TO_READ);
//	print_state(g->cur);
//	print_state(get_state(g->cur, PA));
//	print_state(get_state(g->cur, SA));
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
