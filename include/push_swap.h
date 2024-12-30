/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:00:46 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 02:40:45 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define N_ACTION 11
# ifndef N_STEPS_TO_READ
#  define N_STEPS_TO_READ 1
# endif

# include <ctype.h>
# include <ft_stdio.h>
# include <libft.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>

typedef struct s_dllst	t_dllst;
typedef struct s_state	t_state;
typedef struct s_game	t_game;

typedef t_dllst			t_stack;

struct					s_dllst
{
	int					val;
	struct s_dllst		*prev;
	struct s_dllst		*next;
};

struct					s_state
{
	t_stack				*a;
	t_stack				*b;
};

struct					s_game
{
	t_state				*cur;
};
void					sa(t_state *s);
void					sb(t_state *s);
void					ss(t_state *s);
void					pa(t_state *s);
void					pb(t_state *s);
void					ra(t_state *s);
void					rb(t_state *s);
void					rr(t_state *s);
void					rra(t_state *s);
void					rrb(t_state *s);
void					rrr(t_state *s);
void					raise_err(void);
void					assert_null(void *p, void *to_del, void (*del)(void *));
void					assert_integer(char *s, void *to_del,
							void (*del)(void *));
bool					is_sorted_dll(t_dllst *s);
int						intmin(int *ar, size_t s);
int						intmax(int *ar, size_t s);
void					put_on_arr(t_dllst *n, size_t i, void *param);
t_dllst					**dllst2arr(t_stack *s);
void					swap_addr(void **lhs, void **rhs);
t_dllst					**sorted_arr(t_stack *s);
void					compress(t_stack *s);
void					del_stack(void *ptr);
void					del_state(void *ptr);
void					del_status(void *ptr);
void					dllst_iter(t_dllst *s, void (*f)(t_dllst *s, size_t i,
								void *params), void *params);
void					node_print(t_stack *s, size_t i, void *params);
void					dllst_print(t_stack *s);
void					print_state(t_state *s);
size_t					dllst_len(t_dllst *s);
t_stack					*str2stack(char *s);
t_stack					*int2stack(int i);
bool					equal_stack(t_stack *lhs, t_stack *rhs);
bool					equal_state(t_state *lhs, t_state *rhs);
t_state					*arg2state(int n, char **s);
void					pb_all(t_state *s);
void					sort_large(t_state *s);
void					sort3(t_state *s);
void					sort4(t_state *s);
void					sort5(t_state *s);
t_stack					*pop(t_stack **s);
bool					insert(t_stack **s, t_stack *i);
bool					swap(t_stack **s);
bool					push(t_stack **lhs, t_stack **rhs);
bool					rotate(t_stack **s);
bool					r_rotate(t_stack **s);
ssize_t					find(t_stack *s, int val);
bool					raise_up(t_stack **s, t_state *state, int val);
t_game					*init_game(int c, char **v);
void					validate_arg(int c, char **v);
void					del_game(void *ptr);
void					run_game(t_game *g);
int						main(int argc, char **argv);
#endif
