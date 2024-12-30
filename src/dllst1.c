#include "push_swap.h"

static void	cntup(t_dllst *s, size_t i, void *p)
{
	(void)s;
	(void)i;
	++*(size_t *)p;
}

size_t	dllst_len(t_dllst *s)
{
	if(s == NULL)
		return 0;
	size_t cnt;
	cnt = 0;
	dllst_iter(s, cntup, &cnt);
	return cnt;
}
