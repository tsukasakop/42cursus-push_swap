/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:28:28 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:56:05 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_game	*init_game(int c, char **v)
{
	t_game	*game;

	game = ft_g_mmmalloc(sizeof(t_game));
	assert_null((void *)game);
	game->cur = arg2state(c, v);
	return (game);
}

void	validate_arg(int c, char **v)
{
	if (c == 0)
		raise_err();
	while (c--)
		assert_integer(*v++);
	return ;
}

void	run_game(t_game *g)
{
	size_t	size;

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

int	main(int argc, char **argv)
{
	t_game	*g;

	ft_atexit(ft_g_mmfree);
	validate_arg(argc - 1, argv + 1);
	g = init_game(argc - 1, argv + 1);
	if (is_sorted_dll(g->cur->a))
		raise_err();
	compress(g->cur->a);
	run_game(g);
	ft_exit(EXIT_SUCCESS);
}
