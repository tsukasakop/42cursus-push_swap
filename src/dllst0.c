/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllst0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:28:49 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:41:35 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	dllst_iter(t_dllst *s, void (*f)(t_dllst *s, size_t i, void *params),
		void *params)
{
	t_dllst	*cur;
	size_t	i;

	cur = s;
	i = 0;
	if (s == NULL)
		return ;
	f(cur, i, params);
	cur = cur->next;
	i++;
	while (cur != s)
	{
		f(cur, i, params);
		cur = cur->next;
		i++;
	}
}
