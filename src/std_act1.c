/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_act1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:24:34 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:28:15 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	r_rotate(t_stack **s)
{
	if (dllst_len(*s) < 2)
		return (false);
	*s = (*s)->prev;
	return (true);
}

ssize_t	find(t_stack *s, int val)
{
	t_stack	*cur;
	ssize_t	cnt;

	if (s == NULL)
		return (-1);
	cnt = 0;
	cur = s;
	while (cur->val != val)
	{
		cnt++;
		cur = cur->next;
		if (cur == s)
			return (-1);
	}
	return (cnt);
}

bool	raise_up(t_stack **s, t_state *state, int val)
{
	void	(*f)(t_state *);
	size_t	size;
	ssize_t	cnt;

	cnt = find(*s, val);
	if (cnt == -1)
		return (false);
	size = dllst_len(*s);
	if (cnt < (ssize_t)size / 2 && *s == state->a)
		f = ra;
	else if (cnt < (ssize_t)size / 2 && *s == state->b)
		f = rb;
	else if (cnt >= (ssize_t)size / 2)
	{
		cnt = size - cnt;
		if (*s == state->a)
			f = rra;
		else
			f = rrb;
	}
	while (cnt--)
		f(state);
	return (true);
}
