#include "../includes/ft_traceroute.h"

static void	exit_usage()
{
	printf("Usage: ft_traceroute [Options] target\n"
		"\nOptions:\n"
		"-q Number: send Number probes at each ttl settings\n"
		"-w Number: set Number seconds before a request timeout\n"
		"-p Number: port destination is set to Number\n"
		"-m Number: set the max TTL to Number\n"
		"-f Number: set the first TTL to Number\n"
		"-h:        display this usage\n"
	);
	exit(0);
}

static char	get_opt(char *av[], int *i)
{
	char	ret;

	if (av[*i][0] != '-')
		return '\0';
	ret = av[*i][1];
	*i += 1;
	return ret;
}

static int	try_val(int val, char *error)
{
	if (val > 0)
		return val;
	exit_error(error);
}

static void	set_opt(char opt, char *value, t_env *env)
{
	int		val;

	if (value)
	{
		val = ft_atoi(value);
		if (opt == 'q')
			env->maxprobe = try_val(val, "-q -> bad values");
		else if (opt == 'w')
			env->timeout = try_val(val, "-w -> bad values");
		else if (opt == 'p')
			env->dport = try_val(val, "-p -> bad values");
		else if (opt == 'm')
			env->maxttl = try_val(val, "-m -> bad values");
		else if (opt == 'f')
			env->firstttl = try_val(val, "-w -> bad values");
		return ;
	}
	if (opt == 'h')
		exit_usage();
	printf("%c: ", opt);
	exit_error("bad parameters or value missing, use -h for help");
}

void		parse_args(int ac, char *av[], t_env *env)
{
	int		i;
	char	opt;

	i = 1;
	while (i < ac)
	{
		if ((opt = get_opt(av, &i)))
			set_opt(opt, av[i], env);
		else if (av[i])
		{
			env->target = av[i];
			return ;
		}
		i++;
	}
}

