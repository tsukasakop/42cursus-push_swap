/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:28:28 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 05:03:13 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_game	*init_game(int c, char **v)
{
	t_game	*game;

	game = (t_game *)assert_null(ft_g_mmmalloc(sizeof(t_game)));
	game->cur = arg2state(c, v);
	return (game);
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
	g = init_game(argc - 1, argv + 1);
	compress(g->cur->a);
	if (is_sorted_dll(g->cur->a))
		ft_exit(EXIT_SUCCESS);
	run_game(g);
	ft_exit(EXIT_SUCCESS);
}
