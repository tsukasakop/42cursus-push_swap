/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:21:08 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:22:21 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort3(t_state *s)
{
	int	l;
	int	h;

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
	if (s->b->val == 0)
		pa(s);
	else if (s->b->val == 1)
		(ra(s), pa(s), rra(s));
	else if (s->b->val == 2)
		(rra(s), pa(s), ra(s), ra(s));
	else if (s->b->val == 3)
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
