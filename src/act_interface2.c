/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_interface2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:29:03 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:29:07 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
