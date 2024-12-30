/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:23:42 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:47:30 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	raise_err(void)
{
	ft_fprintf(ft_stderr(), "Error\n");
	ft_exit(EXIT_FAILURE);
}

void	assert_null(void *p, void *to_del, void (*del)(void *))
{
	if (p)
		return ;
	if (to_del && del)
		del(to_del);
	raise_err();
}

void	assert_integer(char *s, void *to_del, void (*del)(void *))
{
	assert_null((void *)s, to_del, del);
	if (*s == '+' || *s == '-')
		s++;
	if (!ft_isdigit(*s))
		raise_err();
	while (ft_isdigit(*s))
		s++;
	if (*s)
		raise_err();
}
