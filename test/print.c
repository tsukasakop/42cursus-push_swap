void	node_print(t_stack *s, size_t i, void *params)
{
	(void)i;
	(void)params;
	PRINT("%d ", s->val);
}

void	dllst_print(t_stack *s)
{
	dllst_iter(s, node_print, NULL);
	PRINT("\n");
}

void	print_state(t_state *s)
{
	PRINT(".a = ");
	dllst_print(s->a);
	PRINT(".b = ");
	dllst_print(s->b);
}
