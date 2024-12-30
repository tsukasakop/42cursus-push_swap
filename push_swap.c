#include "push_swap.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/errno.h>
#include <limits.h>

void	node_print(t_stack *s, size_t i, void *params)
{
	(void)i;
	(void)params;
	PRINT("%d ", s->val);
}

void	dllst_iter(t_dllst *s, void(*f)(t_dllst *s, size_t i, void *params), void *params)
{
	t_dllst *cur;
	cur = s;
	size_t i;
	i = 0;
	if(s == NULL)
		return;
	f(cur, i, params);
	cur = cur->next;
	i++;
	while (cur != s)
	{
		f(cur, i, params);
		cur = cur->next;
		i++;
	}
}

void	dllst_print(t_stack *s)
{
	dllst_iter(s, node_print, NULL);
	PRINT("\n");
}

void	print_state(t_state *s)
{
	PRINT(".a = ");
	dllst_print(s->a);
	PRINT(".b = ");
	dllst_print(s->b);
}

static void	cntup(t_dllst *s, size_t i, void *p)
{
	(void)s;
	(void)i;
	++*(size_t *)p;
}

size_t	dllst_len(t_dllst *s)
{
	if(s == NULL)
		return 0;
	size_t cnt;
	cnt = 0;
	dllst_iter(s, cntup, &cnt);
	return cnt;
}


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
	state->b = NULL;
	return state;	
}

t_game *init_game(int c, char** v)
{
	t_game *game;
	game = malloc(sizeof(t_game));
	assert_null((void *)game, NULL, NULL);
	game->cur = arg2state(c, v);
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

t_stack	*pop(t_stack **s)
{
	t_stack *ret;

	if (dllst_len(*s) == 0)
		return NULL;
	if (dllst_len(*s) == 1)
	{
		ret = *s;
		*s = NULL;
		return ret;
	}
	ret = *s;
	(*s)->prev->next = (*s)->next;
	(*s)->next->prev = (*s)->prev;
	*s = (*s)->next;
	return ret;
}

bool	insert(t_stack **s, t_stack *i)
{
	if(i == NULL)
		return false;
	if (dllst_len(*s) == 0)
	{
		i->next = i;
		i->prev = i;
	}
	else
	{
		i->next = *s;
		i->prev = (*s)->prev;
		(*s)->prev->next = i;
		(*s)->prev = i;
	}
	*s = i;
	return true;
}

bool	swap(t_stack **s)
{
	if (dllst_len(*s) < 2)
		return false;
	if ((*s)->next == (*s)->prev)
		return rotate(s);
	t_stack *tmp = pop(s);
	rotate(s);
	insert(s, tmp);
	r_rotate(s);
	/*
	(*s)->prev->next = (*s)->next;
	(*s)->next->next->prev = (*s);
	(*s)->next->prev = (*s)->prev;
	(*s)->prev = (*s)->next;
	(*s)->next = (*s)->next->next;
	(*s)->next->next = (*s);
	*/
	return true;
}

bool	push(t_stack **lhs, t_stack **rhs)
{
	t_stack *tmp;

	if (dllst_len(*lhs) == 0)
		return false;
	tmp = pop(lhs);
	if(tmp == NULL)
		return false;
	return insert(rhs, tmp);
}

bool	rotate(t_stack **s)
{
	if (dllst_len(*s) < 2)
		return false;
	*s = (*s)->next;
	return true;
}

bool	r_rotate(t_stack **s)
{
	if (dllst_len(*s) < 2)
		return false;
	*s = (*s)->prev;
	return true;
}

ssize_t	find(t_stack *s, int val)
{
	t_stack *cur;
	ssize_t cnt;

	if(s == NULL)
		return -1;
	cnt = 0;
	cur = s;
	while(cur->val != val)
	{
		cnt++;
		cur = cur->next;
		if(cur == s)
			return -1;
	}
	return cnt;
}

bool	raise_up(t_stack **s, t_state *state, int val)
{
	void (*f)(t_state *);
	size_t size;
	ssize_t cnt;

	cnt = find(*s, val);
	if (cnt == -1)
		return false;
	size = dllst_len(*s);
	if(cnt < size / 2)
	{
		if (*s == state->a)
			f = ra;
		else
			f = rb;
	}
	else
	{
		cnt = size - cnt;
		if (*s == state->a)
			f = rra;
		else
			f = rrb;
	}
	while(cnt--)
		f(state);
	return true;
}

void	sa(t_state *s)
{
	if(swap(&s->a))
		ft_printf("sa\n");
}

void	sb(t_state *s)
{
	if(swap(&s->b))
		ft_printf("sb\n");
}

void	ss(t_state *s)
{
	if(dllst_len(s->b) >= 2 && dllst_len(s->b))
	{
		sa(s);
		sb(s);
		ft_printf("ss\n");
	}
}

void	pa(t_state *s)
{
	if (push(&s->b, &s->a))
		ft_printf("pa\n");
}

void	pb(t_state *s)
{
	if (push(&s->a, &s->b))
		ft_printf("pb\n");
}

void	ra(t_state *s)
{
	if (rotate(&s->a))
		ft_printf("ra\n");
}

void	rb(t_state *s)
{
	if (rotate(&s->b))
		ft_printf("rb\n");
}

void	rr(t_state *s)
{
	if (dllst_len(s->a) >= 2 && dllst_len(s->b) >= 2)
	{
		ra(s);
		rb(s);
		ft_printf("rr\n");
	}
}

void	rra(t_state *s)
{
	if (r_rotate(&s->a))
		ft_printf("rra\n");
}

void	rrb(t_state *s)
{
	if (r_rotate(&s->b))
		ft_printf("rrb\n");
}

void	rrr(t_state *s)
{
	if (dllst_len(s->a) >= 2 && dllst_len(s->b) >= 2)
	{
		rra(s);
		rrb(s);
		ft_printf("rrr\n");
	}
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

bool	is_sorted_dll(t_dllst *s) 
{
	if(s == NULL)
		return true;
	t_dllst *cur;
	int prev;
	prev = s->val;
	cur = s->next;
	while (cur != s)
	{
		if (cur->val < prev)
			return false;
		prev = cur->val;
		cur = cur->next;
	}
	return true;
}

int intmin(int *ar, size_t s)
{
	int min;
	min = INT_MAX;
	while(s--)
	{
		if (*ar < min)
			min = *ar;
		ar++;
	}
	return min;
}

int intmax(int *ar, size_t s)
{
	int max;
	max = INT_MIN;
	while(s--)
	{
		if (*ar > max)
			max = *ar;
		ar++;
	}
	return max;
}

void	sort3(t_state *s)
{
	int l;
	int h;

	l = intmin((int [3]){s->a->val, s->a->next->val, s->a->next->next->val}, 3);
	h = intmax((int [3]){s->a->val, s->a->next->val, s->a->next->next->val}, 3);
	if (s->a->val == l && s->a->prev->val == h)
		;
	else if (s->a->val == l && s->a->next->val == h)
		(sa(s), ra(s));
	else if (s->a->prev->val == l && s->a->next->val == h)
		rra(s);
	else if (s->a->prev->val == h && s->a->next->val == l)
		sa(s);
	else if (s->a->val == h && s->a->next->val == l)
		ra(s);
	else if (s->a->val == h && s->a->prev->val == l)
		(ra(s), sa(s));
}

void	sort4(t_state *s)
{
	pb(s);
	sort3(s);
	if(s->b->val == 0)
		pa(s);
	else if(s->b->val == 1)
		(ra(s), pa(s), rra(s));
	else if(s->b->val == 2)
		(rra(s), pa(s), ra(s), ra(s));
	else if(s->b->val == 3)
		(pa(s), ra(s));
}
void	sort5(t_state *s)
{
	raise_up(&s->a, s, 4);
	pb(s);
	sort4(s);
	pa(s);
	ra(s);
}

void	pb_all(t_state *s)
{
	size_t border;
	size_t size;
	size = dllst_len(s->a);
	border = size / 20;
	while(size)
	{
		if(s->a->val > border)
		{
			if(s->b && s->b->val > s->a->val)
				rr(s);
			else
				ra(s);
			continue;
		}
		pb(s);
		size--;
		border++;
	}
}

void	sort_large(t_state *s)
{
	size_t size;
	size = dllst_len(s->a);
	pb_all(s);
	while(size)
	{
		raise_up(&s->b, s, (int)size - 1);
		pa(s);
		size--;
	}
}

void	run_game(t_game *g)
{
	size_t size;
	size = dllst_len(g->cur->a);
	if (size == 2)
		sa(g->cur);
	else if (size == 3)
		sort3(g->cur);
	else if (size == 4)
		sort4(g->cur);
	else if (size == 5)
		sort5(g->cur);
	else
		sort_large(g->cur);
}

void	test_state(t_game *g)
{
	print_state(g->cur);
	PRINT("Test pa\n");
	pa(g->cur);
	print_state(g->cur);
	PRINT("Test pa\n");
	pa(g->cur);
	print_state(g->cur);
	PRINT("Test pa\n");
	pa(g->cur);
	print_state(g->cur);
	PRINT("Test pa\n");
	pa(g->cur);
	print_state(g->cur);
	PRINT("Test pb\n");
	pb(g->cur);
	print_state(g->cur);
	PRINT("Test sa\n");
	sa(g->cur);
	print_state(g->cur);
	PRINT("Test sb\n");
	sb(g->cur);
	print_state(g->cur);
	PRINT("Test ss\n");
	ss(g->cur);
	print_state(g->cur);
	PRINT("Test ra\n");
	ra(g->cur);
	print_state(g->cur);
	PRINT("Test rb\n");
	rb(g->cur);
	print_state(g->cur);
	PRINT("Test rr\n");
	rr(g->cur);
	print_state(g->cur);
	PRINT("Test rra\n");
	rra(g->cur);
	print_state(g->cur);
	PRINT("Test rrb\n");
	rrb(g->cur);
	print_state(g->cur);
	PRINT("Test rrr\n");
	rrr(g->cur);
	print_state(g->cur);
}

void	put_on_arr(t_dllst *n, size_t i, void *param)
{
	((t_dllst **)param)[i] = n;
}

t_dllst	**dllst2arr(t_stack *s)
{
	t_dllst **ar;

	ar = (t_dllst **)calloc(sizeof(t_dllst *),dllst_len(s) + 1);
	if (ar == NULL)
		raise_err("malloc failed");
	dllst_iter(s, put_on_arr, (void *)ar);
	return ar;
}

void	swap_addr(void **lhs, void **rhs)
{
	void *tmp;

	tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
	return;
}

t_dllst	**sorted_arr(t_stack *s)
{
	t_dllst **ar;

	ar = dllst2arr(s);
	size_t i;
	size_t j;
	i = 0;
	j = 0;
	while(ar[i])
	{
		j = i + 1;
		while(ar[j])
		{
			if (ar[j]->val < ar[i]->val)
				swap_addr((void **)&ar[i], (void **)&ar[j]);
			j++;
		}
		i++;
	}
	return ar;
}

void	compress(t_stack *s)
{
	t_dllst **ar;

	ar = sorted_arr(s);
	size_t i;
	i = 0;
	while(ar[i])
	{
		ar[i]->val = (int)i;
		i++;
	}
	free(ar);
}

int main(int argc, char** argv)
{
	t_game *g;

	validate_arg(argc-1, argv+1);
	g = init_game(argc-1, argv+1);
	if(is_sorted_dll(g->cur->a))
		exit(EXIT_SUCCESS);
	compress(g->cur->a);
	print_state(g->cur);
	run_game(g);
	print_state(g->cur);
	//test_state(g);
	del_game(g);
	exit(EXIT_SUCCESS);
}
