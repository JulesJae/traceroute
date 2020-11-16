#include "../includes/ft_traceroute.h"
#include <errno.h>

struct addrinfo	*Getaddrinfo(char *s, int af, int socktype, int proto)
{
	struct addrinfo	hints;
	struct addrinfo	*res;

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = af;
	hints.ai_socktype = socktype;
	hints.ai_protocol = proto;
	if (getaddrinfo(s, NULL, &hints, &res) != 0)
		exit_error("Unknown host or service");
	return res;
}

void			Setsockopt(int fd, int lvl, int optname, void *optval
, socklen_t len)
{
	if (setsockopt(fd, lvl, optname, optval, len) < 0)
		exit_error("Setsockopt error");
}

void			Bind(int fd, struct sockaddr *sa, socklen_t len)
{
	if (bind(fd, sa, len) == -1)
		exit_error("Bind error");
}

void			Sendto(int fd, void *buf, size_t len, struct sockaddr *sa
	, socklen_t salen)
{
	if (sendto(fd, buf, len, 0, sa, salen) == -1)
		exit_error("Sendto error");
}

int				Socket(int domain, int type, int proto)
{
	int		sfd;

	sfd = socket(domain, type, proto);
	if (sfd == -1)
		exit_error("Socket error");
	return sfd;
}