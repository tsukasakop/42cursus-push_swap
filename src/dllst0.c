#include "push_swap.h"

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

void	node_print(t_stack *s, size_t i, void *params)
{
	(void)i;
	(void)params;
	PRINT("%d ", s->val);
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
