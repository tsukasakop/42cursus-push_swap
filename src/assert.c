/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:23:42 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:54:57 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	raise_err(void)
{
	ft_fprintf(ft_stderr(), "Error\n");
	ft_exit(EXIT_FAILURE);
}

void	assert_null(void *p)
{
	if (p)
		return ;
	raise_err();
}

void	assert_integer(char *s)
{
	assert_null((void *)s);
	if (*s == '+' || *s == '-')
		s++;
	if (!ft_isdigit(*s))
		raise_err();
	while (ft_isdigit(*s))
		s++;
	if (*s)
		raise_err();
}
