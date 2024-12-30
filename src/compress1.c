/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:23:19 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:53:18 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	put_on_arr(t_dllst *n, size_t i, void *param)
{
	((t_dllst **)param)[i] = n;
}

t_dllst	**dllst2arr(t_stack *s)
{
	t_dllst	**ar;

	ar = (t_dllst **)ft_g_mmcalloc(sizeof(t_dllst *), dllst_len(s) + 1);
	if (ar == NULL)
		raise_err();
	dllst_iter(s, put_on_arr, (void *)ar);
	return (ar);
}

void	swap_addr(void **lhs, void **rhs)
{
	void	*tmp;

	tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
	return ;
}

t_dllst	**sorted_arr(t_stack *s)
{
	t_dllst	**ar;
	size_t	i;
	size_t	j;

	ar = dllst2arr(s);
	i = 0;
	j = 0;
	while (ar[i])
	{
		j = i + 1;
		while (ar[j])
		{
			if (ar[j]->val < ar[i]->val)
				swap_addr((void **)&ar[i], (void **)&ar[j]);
			j++;
		}
		i++;
	}
	return (ar);
}

void	compress(t_stack *s)
{
	t_dllst	**ar;
	size_t	i;

	ar = sorted_arr(s);
	i = 0;
	while (ar[i])
	{
		ar[i]->val = (int)i;
		i++;
	}
}
