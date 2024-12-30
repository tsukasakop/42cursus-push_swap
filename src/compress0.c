#include "push_swap.h"

bool	is_sorted_dll(t_dllst *s) 
{
	if(s == NULL)
		return true;
	t_dllst *cur;
	int prev;
	prev = s->val;
	cur = s->next;
	while (cur != s)
	{
		if (cur->val < prev)
			return false;
		prev = cur->val;
		cur = cur->next;
	}
	return true;
}

int intmin(int *ar, size_t s)
{
	int min;
	min = INT_MAX;
	while(s--)
	{
		if (*ar < min)
			min = *ar;
		ar++;
	}
	return min;
}

int intmax(int *ar, size_t s)
{
	int max;
	max = INT_MIN;
	while(s--)
	{
		if (*ar > max)
			max = *ar;
		ar++;
	}
	return max;
}
