#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#define N_ACTION 11

typedef enum e_action
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
}	t_action;

typedef struct s_stack
{
	int val;
	struct s_stack *prev;
	struct s_stack *next;
}	t_stack;

typedef struct s_state
{
	int	score;
	t_stack	*a;
	t_stack	*b;
	struct s_state *ch[N_ACTION];
}	t_state;

typedef struct
{
}	t_set;

typedef struct
{
	t_state *cur;
	t_set *set;
}	t_game;

void	swap(t_stack **s);
void	push(t_stack **lhs, t_stack **rhs);
void	rotate(t_stack **s);
void	r_rotate(t_stack **s);

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
void	del_state(t_state* s);
void	calc_score(t_state* s);

t_state* arg2state(int c, char **v);
t_game* init_game(int c, char **v);
void	run_game(t_game*, int gen);

void	validate_arg(int, char**);
#endif
