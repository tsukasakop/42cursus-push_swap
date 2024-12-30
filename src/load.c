/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:29:53 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 05:23:55 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long	ft_strtoll(const char *s)
{
	long long	d;
	long long	sign;

	d = 0;
	sign = 1;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		++s;
	while (*s)
	{
		if (!ft_isdigit(*s))
			raise_err();
		if (sign == 1 && d > LLONG_MAX - (*s - '0') / 10)
			raise_err();
		if (sign == -1 && d < LLONG_MIN + (*s - '0') / 10)
			raise_err();
		d = d * 10 + sign * (*s - '0');
		s++;
	}
	return (d);
}

t_stack	*str2stack(char *s)
{
	t_stack		*p;
	long long	v;

	p = ft_g_mmmalloc(sizeof(t_stack));
	if (!p)
		return (NULL);
	v = ft_strtoll((const char *)s);
	if (v > (long long)INT_MAX || v < (long long)INT_MIN)
		raise_err();
	p->val = (int)v;
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

t_state	*arg2state(int n, char **s)
{
	t_state	*state;
	t_stack	*cur;

	state = (t_state *)assert_null((void *)ft_g_mmcalloc(sizeof(t_state), 1));
	while (n--)
	{
		if (state->a == NULL)
		{
			state->a = (t_stack *)assert_null((void *)str2stack(*s));
			cur = state->a;
		}
		else
		{
			cur->next = (t_stack *)assert_null((void *)str2stack(*s));
			cur->next->prev = cur;
			cur = cur->next;
		}
		s++;
	}
	cur->next = state->a;
	state->a->prev = cur;
	state->b = NULL;
	return (state);
}
