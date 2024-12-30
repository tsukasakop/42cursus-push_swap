/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_interface1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:23:53 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:23:55 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
