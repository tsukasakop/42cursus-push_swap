/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_act0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:23:02 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:23:06 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*pop(t_stack **s)
{
	t_stack	*ret;

	if (dllst_len(*s) == 0)
		return (NULL);
	if (dllst_len(*s) == 1)
	{
		ret = *s;
		*s = NULL;
		return (ret);
	}
	ret = *s;
	(*s)->prev->next = (*s)->next;
	(*s)->next->prev = (*s)->prev;
	*s = (*s)->next;
	return (ret);
}

bool	insert(t_stack **s, t_stack *i)
{
	if (i == NULL)
		return (false);
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
	return (true);
}

bool	swap(t_stack **s)
{
	t_stack	*tmp;

	if (dllst_len(*s) < 2)
		return (false);
	if ((*s)->next == (*s)->prev)
		return (rotate(s));
	tmp = pop(s);
	rotate(s);
	insert(s, tmp);
	r_rotate(s);
	return (true);
}

bool	push(t_stack **lhs, t_stack **rhs)
{
	t_stack	*tmp;

	if (dllst_len(*lhs) == 0)
		return (false);
	tmp = pop(lhs);
	if (tmp == NULL)
		return (false);
	return (insert(rhs, tmp));
}

bool	rotate(t_stack **s)
{
	if (dllst_len(*s) < 2)
		return (false);
	*s = (*s)->next;
	return (true);
}
