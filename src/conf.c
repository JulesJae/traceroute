#include "../includes/ft_traceroute.h"

static void	configure_ipv6_rcv(t_env *env)
{
	int		padding;

	env->pkt6.ip = (struct ip6_hdr*)env->recvbuf;
	padding = sizeof(struct ip6_hdr);
	env->pkt6.hlen = sizeof(struct ip6_hdr);
	env->pkt6.icmp6 = (struct icmp6_hdr*)(env->recvbuf + padding);
	padding += ICMPH_S;
	env->pkt6.hip = (struct ip6_hdr*)(env->recvbuf + padding);
	padding += sizeof(struct ip6_hdr);
	env->udp = (struct udphdr*)(env->recvbuf + padding);
}

static void	configure_ipv4_rcv(t_env *env)
{
	int		padding;

	env->pkt4.ip = (struct iphdr*)env->recvbuf;
	padding = sizeof(struct iphdr);
	env->pkt4.hlen = padding;
	env->pkt4.icmp = (struct icmphdr*)(env->recvbuf + padding);
	padding += ICMPH_S;
	env->pkt4.hip = (struct iphdr*)(env->recvbuf + padding);
	padding += sizeof(struct iphdr);
	env->udp = (struct udphdr*)(env->recvbuf + padding);
}


void		configure_sending(t_env *env)
{
	env->sendfd = Socket(env->addr.af, SOCK_DGRAM, 0);
	env->recvfd = Socket(env->addr.af, SOCK_RAW, env->addr.icmpproto);
	env->sabind->sa_family = env->addr.sa->sa_family;
	env->sport = (getpid() & 0xffff) | 0x8000;
	sock_set_port(env->sabind, env->addr.salen, htons(env->sport));
	Bind(env->sendfd, env->sabind, env->addr.salen);
	env->msg = (t_msg*)env->sendbuf;
}

void		configure_receive(t_env *env)
{
	struct timeval	tv;

	tv.tv_sec = env->timeout;
	tv.tv_usec = 50000;
	Setsockopt(env->recvfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	if (env->addr.af == AF_INET6)
		configure_ipv6_rcv(env);
	else
		configure_ipv4_rcv(env);
}