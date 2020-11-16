#include "../includes/ft_traceroute.h"

static void		set_env_for_in(struct addrinfo *res, t_env *env)
{
	struct sockaddr_in	*addr;

	addr = (struct sockaddr_in*)res->ai_addr;
	inet_ntop(AF_INET, (void*)&addr->sin_addr, env->addr.ipstr, INET_ADDRSTRLEN);
	env->addr.icmpproto = IPPROTO_ICMP;
	env->addr.salen = sizeof(struct sockaddr_in);
	env->ttllvl = IPPROTO_IP;
	env->ttloptname = IP_TTL;
	env->recv = recv4;
}

static void		set_env_for_in6(struct addrinfo *res, t_env *env)
{
	struct sockaddr_in6	*addr6;

	addr6 = (struct sockaddr_in6*)res->ai_addr;
	inet_ntop(AF_INET6, (void*)&addr6->sin6_addr, env->addr.ipstr, INET6_ADDRSTRLEN);
	env->addr.icmpproto = IPPROTO_ICMPV6;
	env->addr.salen = sizeof(struct sockaddr_in6);
	env->ttllvl = IPPROTO_IPV6;
	env->ttloptname = IPV6_UNICAST_HOPS;
	env->recv = recv6;
}

void			get_addr(char *addr_p, t_env *env)
{
	struct addrinfo		*res;

	res = Getaddrinfo(addr_p, AF_UNSPEC, SOCK_DGRAM, IPPROTO_UDP);
	if (res->ai_family == AF_INET)
		set_env_for_in(res, env);
	else if (res->ai_family == AF_INET6)
		set_env_for_in6(res, env);
	env->addr.sa = res->ai_addr;
	env->addr.af = res->ai_family;
	env->sabind = malloc(env->addr.salen);
	ft_bzero(env->sabind, env->addr.salen);
	env->sarecv = malloc(env->addr.salen);
	ft_bzero(env->sarecv, env->addr.salen);
	env->salast = malloc(env->addr.salen);
	ft_bzero(env->salast, env->addr.salen);
}