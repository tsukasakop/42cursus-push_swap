/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:29:53 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:56:45 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*str2stack(char *s)
{
	t_stack	*p;

	p = ft_g_mmmalloc(sizeof(t_stack));
	if (!p)
		return (NULL);
	p->val = ft_atoi((const char *)s);
	p->prev = NULL;
	p->next = NULL;
	return (p);
}

t_stack	*int2stack(int i)
{
	t_stack	*p;

	p = ft_g_mmmalloc(sizeof(t_stack));
	if (!p)
		return (NULL);
	p->val = i;
	p->prev = NULL;
	p->next = NULL;
	return (p);
}

bool	equal_stack(t_stack *lhs, t_stack *rhs)
{
	t_stack	*cur_l;
	t_stack	*cur_r;

	cur_l = lhs;
	cur_r = rhs;
	if (!cur_l || !cur_r)
		return (cur_l == cur_r);
	if (cur_l->val != cur_r->val)
		return (false);
	while (cur_l != lhs || cur_r != rhs)
	{
		if (cur_l->val != cur_r->val)
			return (false);
		cur_l = cur_l->next;
		cur_r = cur_r->next;
	}
	return (cur_l == lhs && cur_r == rhs);
}

bool	equal_state(t_state *lhs, t_state *rhs)
{
	return (equal_stack(lhs->a, rhs->a) && equal_stack(lhs->b, rhs->b));
}

t_state	*arg2state(int n, char **s)
{
	t_state	*state;
	t_stack	*cur;

	state = (t_state *)ft_g_mmcalloc(sizeof(t_state), 1);
	assert_null((void *)state);
	state->a = str2stack(*s);
	assert_null((void *)state->a);
	cur = state->a;
	while (--n)
	{
		cur->next = str2stack(*++s);
		assert_null((void *)cur->next);
		cur->next->prev = cur;
		cur = cur->next;
	}
	cur->next = state->a;
	state->a->prev = cur;
	state->b = NULL;
	return (state);
}
