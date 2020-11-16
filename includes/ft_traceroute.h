#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netinet/ip_icmp.h>
# include <netinet/udp.h>
# include <netinet/ip6.h>
# include <netinet/icmp6.h>
# include <netdb.h>
# include <sys/time.h>
# include <string.h>
# include <arpa/inet.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>

# define MTU 1500

# define ICMPH_S 8

# define ROUTER -1
# define TARGET -2
# define TIMEOUT -3

# define D_PORT 32778 + 666

typedef struct				s_msg
{
	u_short					msg_seq;
	struct timeval			tv;
}							t_msg;

typedef struct				s_packet6
{
	struct ip6_hdr			*ip;
	struct ip6_hdr			*hip;
	struct icmp6_hdr		*icmp6;
	int						hlen;
}							t_pkt6;

typedef struct				s_pkt4
{
	struct iphdr			*ip;
	struct iphdr			*hip;
	struct icmphdr			*icmp;
	int						hlen;
}							t_pkt4;

typedef struct				s_addr
{
	int						af;
	char					ipstr[INET6_ADDRSTRLEN];
	int						icmpproto;
	struct sockaddr			*sa;
	socklen_t				salen;
}							t_addr;

typedef struct				s_tr
{
	t_addr					addr;
	int						recvfd;
	int						sendfd;
	char					sendbuf[MTU];
	char					recvbuf[MTU];
	char					*target;
	u_short					sport;
	u_short					dport;
	int						ttllvl;
	int						ttloptname;
	int						timeout;
	int						maxttl;
	int						firstttl;
	int						maxprobe;
	int						seq;
	int 					(*recv)(struct s_tr*);
	bool					finish;
	char					ipstr[INET6_ADDRSTRLEN];
	struct timeval			tv_rcv;
	struct sockaddr			*sabind;
	struct sockaddr			*sarecv;
	struct sockaddr			*salast;
	struct udphdr			*udp;
	t_pkt6					pkt6;
	t_pkt4					pkt4;
	t_msg					*msg;
}							t_env;

/* ---------------------------------- Wrapper ---------------------------------- */

struct addrinfo				*Getaddrinfo(char *addr_s, int af
	, int sockt, int prot);
int							Socket(int domain, int type, int proto);
void						Bind(int fd, struct sockaddr *sa, socklen_t len);
void						Sendto(int fd, void *buf, size_t len
	, struct sockaddr *sa, socklen_t salen);
void						Setsockopt(int fd, int lvl, int optname, void *optval
	, socklen_t len);

/* ---------------------------------- Lib ---------------------------------- */

void						exit_error(char *s);
void						ft_bzero(void *data, size_t len);
void						ft_memcpy(void *dest, void *src, size_t len);
int     					ft_atoi(const char *str);

/* ---------------------------------- Prog ---------------------------------- */

void						parse_args(int ac, char *av[], t_env *env);
void						get_addr(char *addr_p, t_env *env);
void						sock_set_port(struct sockaddr *sa, socklen_t salen
	, ushort port);
int							recv6(t_env *env);
int							recv4(t_env *env);
void						configure_receive(t_env *env);
void						configure_sending(t_env *env);
bool						is_same_addr(struct sockaddr *sa1
	, struct sockaddr *sa2, socklen_t len);
void						ft_traceroute(t_env *env);

#endif