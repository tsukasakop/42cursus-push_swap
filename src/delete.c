#include "push_swap.h"

void	del_stack(void *ptr)
{
	t_stack *cur;
	t_stack *tmp;
	if(!ptr)
		return;
	t_stack *p;
	p = (t_stack *)ptr;
	cur = p->next;
	free(p);
	while(cur && cur != p)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
}

void	del_state(void *ptr)
{
	t_state *p;
	if(!ptr)
		return;
	p = (t_state *)ptr;
	if(p->a)
		del_stack(p->a);
	if(p->b)
		del_stack(p->b);
	free(p);
}

void	del_status(void *ptr)
{
	t_state *p;
	if(!ptr)
		return;
	p = (t_state *)ptr;
	if(p->a)
		del_stack(p->a);
	if(p->b)
		del_stack(p->b);
	free(p);
}
