#include "../includes/ft_traceroute.h"
#include <errno.h>

int			recv6(t_env *env)
{
	int			n;
	socklen_t	len;

	len = env->addr.salen;
	n = recvfrom(env->recvfd, env->recvbuf, MTU, 0, env->sarecv, &len);
	if (n < 0) {
		if (errno == EWOULDBLOCK)
			return TIMEOUT;
		perror("RECVFROM");
		exit_error("Recvfrom Error");
	}
	gettimeofday(&env->tv_rcv, NULL);
	if (env->pkt6.icmp6->icmp6_type == ICMP6_TIME_EXCEEDED
		&& env->pkt6.icmp6->icmp6_code == ICMP6_TIME_EXCEED_TRANSIT)
	{
		if (env->pkt6.hip->ip6_ctlun.ip6_un1.ip6_un1_nxt == IPPROTO_UDP
			&& env->udp->uh_sport == htons(env->sport)
			&& env->udp->uh_dport == htons(env->dport))
				return ROUTER;
	} else if (env->pkt6.icmp6->icmp6_type == ICMP6_DST_UNREACH)
	{
		if (env->udp->uh_sport == htons(env->sport)
			&& env->udp->uh_dport == htons(env->dport))
				return TARGET;
	}
	if (env->udp->uh_sport != htons(env->sport)
			&& env->udp->uh_dport != htons(env->dport))
	return env->pkt6.icmp6->icmp6_code;
}

int			recv4(t_env *env)
{
	int			n;
	socklen_t	len;

	len = env->addr.salen;
	n = recvfrom(env->recvfd, env->recvbuf, MTU, 0, env->sarecv, &len);
	if (n < 0) {
		if (errno == EWOULDBLOCK)
			return TIMEOUT;
		exit_error("Recvfrom Error");
	}
	gettimeofday(&env->tv_rcv, NULL);
	if (env->pkt4.icmp->type == ICMP_TIME_EXCEEDED
		&& env->pkt4.icmp->code == ICMP_TIMXCEED_INTRANS)
	{
		if (env->udp->uh_sport == htons(env->sport)
			&& env->udp->uh_dport == htons(env->dport))
			return ROUTER;
	} else if (env->pkt4.icmp->type == ICMP_DEST_UNREACH)
	{
		if (env->udp->uh_sport == htons(env->sport)
			&& env->udp->uh_dport == htons(env->dport))
				return TARGET;
	}
	printf("toto\n");
	return env->pkt4.icmp->code;
}