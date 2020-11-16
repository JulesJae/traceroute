#include "../includes/ft_traceroute.h"

static void		get_ip_str(struct sockaddr *sa, t_env *env)
{
	struct sockaddr_in	*sa_in;
	struct sockaddr_in6	*sa_in6;

	if (sa->sa_family == AF_INET6)
	{
		sa_in6 = (struct sockaddr_in6*)sa;
		inet_ntop(sa->sa_family, &sa_in6->sin6_addr, env->ipstr, INET6_ADDRSTRLEN);
	} else
	{
		sa_in = (struct sockaddr_in*)sa;
		inet_ntop(sa->sa_family, &sa_in->sin_addr, env->ipstr, INET_ADDRSTRLEN);
	}
}

static void		display_probe_infos(t_env *env)
{
	double		rtt;

	if (!is_same_addr(env->salast, env->sarecv, env->addr.salen))
	{
		get_ip_str(env->sarecv, env);
		printf(" %s (%s)", env->ipstr, env->ipstr);
		ft_memcpy(env->salast, env->sarecv, env->addr.salen);
	}
	rtt = (env->tv_rcv.tv_usec - env->msg->tv.tv_usec) / 1000000.0;
	rtt += (env->tv_rcv.tv_sec - env->msg->tv.tv_sec);
	rtt *= 1000.0;
	printf(" %.3f ms", rtt);
}

static void		send_probes(t_env *env)
{
	int		probe;
	int		code;

	probe = 1;
	while (probe <= env->maxprobe)
	{
		gettimeofday(&env->msg->tv, NULL);
		sock_set_port(env->addr.sa, env->addr.salen, htons(env->dport));
		Sendto(env->sendfd, env->sendbuf, MTU, env->addr.sa, env->addr.salen);
		if ((code = env->recv(env)) == TIMEOUT)
			printf(" *");
		else
		{
			display_probe_infos(env);
			if (code == TARGET)
				env->finish = true;
		}
		probe++;
		env->dport++;
	}
	ft_bzero(env->salast, env->addr.salen);
}

void			ft_traceroute(t_env *env)
{
	int		ttl;

	ttl = env->firstttl;
	configure_sending(env);
	configure_receive(env);
	printf("traceroute to %s (%s): %d hops max, %ld data bytes\n"
		, env->target, env->addr.ipstr, env->maxttl, sizeof(t_msg)
	);
	while (ttl <= env->maxttl && !env->finish)
	{
		Setsockopt(env->sendfd, env->ttllvl, env->ttloptname, &ttl, sizeof(int));
		printf("%2d ", ttl);
		send_probes(env);
		printf("\n");
		ttl++;
	}
}