#include "push_swap.h"

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
