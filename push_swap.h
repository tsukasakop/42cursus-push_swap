/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:00:46 by tkondo            #+#    #+#             */
/*   Updated: 2024/12/31 00:40:42 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define N_ACTION 11
#ifndef N_STEPS_TO_READ
# define N_STEPS_TO_READ 1
#endif

#define PRINT(...) fprintf(stderr, __VA_ARGS__)
#define ft_printf(...) printf(__VA_ARGS__)
#define ft_fprintf(...) fprintf(__VA_ARGS__)

#include <stdbool.h>

typedef struct s_dllst t_dllst;
typedef struct s_state t_state;
typedef struct s_game t_game;

typedef t_dllst t_stack;

struct s_dllst
{
	int val;
	struct s_dllst *prev;
	struct s_dllst *next;
};

struct s_state
{
	t_stack	*a;
	t_stack	*b;
};

struct s_game
{
	t_state *cur;
};

bool	swap(t_stack **s);
bool	push(t_stack **lhs, t_stack **rhs);
bool	rotate(t_stack **s);
bool	r_rotate(t_stack **s);
void	sa(t_state *s);
void	sb(t_state *s);
void	ss(t_state *s);
void	pa(t_state *s);
void	pb(t_state *s);
void	ra(t_state *s);
void	rb(t_state *s);
void	rr(t_state *s);
void	rra(t_state *s);
void	rrb(t_state *s);
void	rrr(t_state *s);

t_state* get_given_state(int argc, char** argv);
t_state* dup_state(t_state* s);
void	calc_score(t_state* s);

int get_score(t_state *s);

t_state* arg2state(int c, char **v);
t_game* init_game(int c, char **v);

void	validate_arg(int, char**);
#endif
