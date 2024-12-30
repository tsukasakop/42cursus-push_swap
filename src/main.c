#include "push_swap.h"

t_game *init_game(int c, char** v)
{
	t_game *game;
	game = malloc(sizeof(t_game));
	assert_null((void *)game, NULL, NULL);
	game->cur = arg2state(c, v);
	return game;
}

void validate_arg(int c, char** v)
{
	if(c == 0)
		raise_err();
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

void	run_game(t_game *g)
{
	size_t size;
	size = dllst_len(g->cur->a);
	if (size == 2)
		sa(g->cur);
	else if (size == 3)
		sort3(g->cur);
	else if (size == 4)
		sort4(g->cur);
	else if (size == 5)
		sort5(g->cur);
	else
		sort_large(g->cur);
}

int main(int argc, char** argv)
{
	t_game *g;

	validate_arg(argc-1, argv+1);
	g = init_game(argc-1, argv+1);
	if(is_sorted_dll(g->cur->a))
		exit(EXIT_SUCCESS);
	compress(g->cur->a);
	print_state(g->cur);
	run_game(g);
	print_state(g->cur);
	del_game(g);
	exit(EXIT_SUCCESS);
}