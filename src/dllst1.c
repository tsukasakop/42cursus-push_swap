/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:23:31 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:23:35 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	cntup(t_dllst *s, size_t i, void *p)
{
	(void)s;
	(void)i;
	++*(size_t *)p;
}

size_t	dllst_len(t_dllst *s)
{
	size_t	cnt;

	if (s == NULL)
		return (0);
	cnt = 0;
	dllst_iter(s, cntup, &cnt);
	return (cnt);
}
