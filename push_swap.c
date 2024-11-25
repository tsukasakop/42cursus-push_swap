#include "push_swap.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void	raise_err(char *msg)
{
	if (!msg)
		msg = "Error";
	//TODO: Replace to ft_fprintf
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void	assert_null(void * p, void *to_del, void (*del)(void *))
{
	if (p)
		return;
	if (to_del && del)
		del(to_del);
	raise_err("Error: null ptr provided.");
}

void	assert_integer(char *s, void *to_del, void (*del)(void *))
{
	assert_null((void *)s, to_del, del);
	if(*s == '+' || *s == '-')
		s++;
	//TODO: Replace to ft_isdigit
	if(!isdigit(*s))
		raise_err("Error: invalid number provided.");
	while(isdigit(*s))
		s++;
	if (*s)
		raise_err("Error: invalid number provided.");
}

t_stack *str2stack(char *s)
{
	t_stack *p;
	p = malloc(sizeof(t_stack));
	if(!p)
		return NULL;
	// TODO: Replace to ft_atoi
	p->val = atoi((const char *)s);
	p->prev = NULL;
	p->next = NULL;
	return p;
}

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
	size_t i;
	i=0;
	while(i<N_ACTION)
		del_status(p->ch[i++]);
	free(p);
	return;
}

t_state *arg2state(int n, char **s)
{
	t_state *state;
	t_stack *cur;
	// TODO: Replace to ft_calloc
	state = (t_state *)calloc(sizeof(t_state), 1);
	assert_null((void *)state, NULL, NULL);
	state->a = str2stack(*s);
	assert_null((void *)state->a, state, del_status);
	cur = state->a;
	while(--n)
	{
		cur->next = str2stack(*++s);
		assert_null((void *)cur->next, state, del_status);
		cur->next->prev = cur;
		cur = cur->next;
	}
	cur->next = state->a;
	state->a->prev = cur;
	return state;	
}

t_game *init_game(int c, char** v)
{
	t_game *game;
	game = malloc(sizeof(t_game));
	assert_null((void *)game, NULL, NULL);
	game->cur = arg2state(c, v);
	game->set = NULL;
	return game;
}

void validate_arg(int c, char** v)
{
	if(c == 0)
		raise_err("Error: no number");
	while(c--)
		assert_integer(*v++, NULL, NULL);
	return;
}

void del_game(void *ptr)
{
	if(!ptr)
		return;
	t_game *p;
	p = (t_game *)ptr;
	del_status((void *)p->cur);
	free(p);
}

int main(int argc, char** argv)
{
	t_game *g;

	validate_arg(argc-1, argv+1);
	g = init_game(argc-1, argv+1);
	//game_start(g, 3);
	del_game(g);
}
