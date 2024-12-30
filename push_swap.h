#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define N_ACTION 11
#ifndef N_STEPS_TO_READ
# define N_STEPS_TO_READ 1
#endif

#define PRINT(...) printf(__VA_ARGS__)

#include <stdbool.h>

typedef enum e_action t_action;
typedef struct s_dllst t_dllst;
typedef struct s_state t_state;
typedef struct s_game t_game;

typedef t_dllst t_stack;

enum e_action
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
};

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
bool	sa(t_state *s);
bool	sb(t_state *s);
bool	ss(t_state *s);
bool	pa(t_state *s);
bool	pb(t_state *s);
bool	ra(t_state *s);
bool	rb(t_state *s);
bool	rr(t_state *s);
bool	rra(t_state *s);
bool	rrb(t_state *s);
bool	rrr(t_state *s);

t_state* get_given_state(int argc, char** argv);
t_state* dup_state(t_state* s);
void	calc_score(t_state* s);

int get_score(t_state *s);

t_state* arg2state(int c, char **v);
t_game* init_game(int c, char **v);

void	validate_arg(int, char**);
#endif
