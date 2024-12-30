#include "push_swap.h"

void	raise_err()
{
	ft_fprintf(stderr, "Error\n");
	exit(EXIT_FAILURE);
}

void	assert_null(void * p, void *to_del, void (*del)(void *))
{
	if (p)
		return;
	if (to_del && del)
		del(to_del);
	raise_err();
}

void	assert_integer(char *s, void *to_del, void (*del)(void *))
{
	assert_null((void *)s, to_del, del);
	if(*s == '+' || *s == '-')
		s++;
	//TODO: Replace to ft_isdigit
	if(!isdigit(*s))
		raise_err();
	while(isdigit(*s))
		s++;
	if (*s)
	{
		printf("s=%s ", s);
		raise_err();
	}
}
