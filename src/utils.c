#include "../includes/ft_traceroute.h"

void		ft_bzero(void *data, size_t len)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char*)data;
	while (i < len)
	{
		p[i] = 0;
		i++;
	}
}

int     ft_atoi(const char *str)
{
        int     res;
        int     negative;

        negative = 1;
        res = 0;
        while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
                        *str == '\v' || *str == '\f' || *str == '\r'))
                ++str;
        if (*str == '-')
                negative = -1;
        if (*str == '-' || *str == '+')
                ++str;
        while (*str && *str >= '0' && *str <= '9')
        {
                res = res * 10 + (*str - 48);
                ++str;
        }
        return (res * negative);
}

void		ft_memcpy(void *dest, void *src, size_t len)
{
	size_t		i;
	char		*d;
	char		*s;

	i = 0;
	d = (char*)dest;
	s = (char*)src;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
}

bool		is_same_addr(struct sockaddr *sa1, struct sockaddr *sa2
	, socklen_t len)
{
	socklen_t	i;
	char		*s1;
	char		*s2;

	i = 0;
	s1 = (char*)sa1;
	s2 = (char*)sa2;
	while (i < len)
	{
		if (s1[i] != s2[i])
		{
			return false;
		}
		i++;
	}
	return true;
}

void		sock_set_port(struct sockaddr *sa, socklen_t salen, ushort port)
{
	struct sockaddr_in		*sa_in;
	struct sockaddr_in6		*sa_in6;

	if (salen == sizeof(struct sockaddr_in))
	{
		sa_in = (struct sockaddr_in*)sa;
		sa_in->sin_port = port;
	} else if (salen == sizeof(struct sockaddr_in6))
	{
		sa_in6 = (struct sockaddr_in6*)sa;
		sa_in6->sin6_port = port;
	}
}