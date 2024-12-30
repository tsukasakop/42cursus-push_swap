/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_interface0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:22:33 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:22:53 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_state *s)
{
	if (swap(&s->a))
		ft_printf("sa\n");
}

void	sb(t_state *s)
{
	if (swap(&s->b))
		ft_printf("sb\n");
}

void	ss(t_state *s)
{
	if (dllst_len(s->b) >= 2 && dllst_len(s->b))
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
