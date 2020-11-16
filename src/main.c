#include "../includes/ft_traceroute.h"
#include <errno.h>

void	exit_error(char *s)
{
	printf("%s\n", s);
	exit(0);
}

static void	initialize_env(t_env *env)
{
	env->timeout = 5;
	env->seq = 0;
	env->maxttl = 30;
	env->maxprobe = 3;
	env->dport = D_PORT;
	env->firstttl = 1;
}

int		main(int ac, char *av[])
{
	t_env			env;

	if (getuid() != 0)
		exit_error("Operation not permitted");
	if (ac < 2)
		exit_error("parameters missing");
	initialize_env(&env);
	parse_args(ac, av, &env);
	get_addr(env.target, &env);
	ft_traceroute(&env);
	free(env.sabind);
	free(env.sarecv);
	free(env.salast);
	return (0);
}