#include "push_swap.h"

void	pb_all(t_state *s)
{
	size_t border;
	size_t size;
	size = dllst_len(s->a);
	border = size / 20;
	while(size)
	{
		if(s->a->val > (int)border)
		{
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
