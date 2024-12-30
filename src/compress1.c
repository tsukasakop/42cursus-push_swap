#include "push_swap.h"

void	put_on_arr(t_dllst *n, size_t i, void *param)
{
	((t_dllst **)param)[i] = n;
}

t_dllst	**dllst2arr(t_stack *s)
{
	t_dllst **ar;

	ar = (t_dllst **)ft_calloc(sizeof(t_dllst *),dllst_len(s) + 1);
	if (ar == NULL)
		raise_err();
	dllst_iter(s, put_on_arr, (void *)ar);
	return ar;
}

void	swap_addr(void **lhs, void **rhs)
{
	void *tmp;

	tmp = *lhs;
	*lhs = *rhs;
	*rhs = tmp;
	return;
}

t_dllst	**sorted_arr(t_stack *s)
{
	t_dllst **ar;

	ar = dllst2arr(s);
	size_t i;
	size_t j;
	i = 0;
	j = 0;
	while(ar[i])
	{
		j = i + 1;
		while(ar[j])
		{
			if (ar[j]->val < ar[i]->val)
				swap_addr((void **)&ar[i], (void **)&ar[j]);
			j++;
		}
		i++;
	}
	return ar;
}

void	compress(t_stack *s)
{
	t_dllst **ar;

	ar = sorted_arr(s);
	size_t i;
	i = 0;
	while(ar[i])
	{
		ar[i]->val = (int)i;
		i++;
	}
	free(ar);
}
