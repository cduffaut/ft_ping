#ifndef PING_H
#define PING_H

#pragma once

#include "../libft/libft.h"

#define DEBOG 	printf("\n\e[1;32m OK: %d, in %s, in the file: %s\n\e[0m\n", __LINE__, __func__, __FILE__);

#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <netinet/ip_icmp.h>
#include <time.h> 

// Colors Set
#define BLACK "\e[1;30m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[1;34m"
#define PINK "\e[1;35m"
#define CYAN "\e[1;36m"
#define RESET "\e[0m"

// NO_PORT is zero it means select any available local port.
#define NO_PORT 0
// #define PACKET_SIZE 64
#define PACKET_SIZE 32

typedef struct s_linked_list
{
	float	nbr;
	struct	s_linked_list	*next;
}				t_linked_list;

typedef struct s_ping_list
{
	char			*hostname;
	char			*ip; // to free
	
	struct sockaddr_in addr_hostname;

	bool			verbose;

	int				len_addr_hostname;
	int				fd;

	int				msg_sended;
	int				msg_received;
	long double		total_time;

	float			min; 
	float			avg; 
	float			max;
	float			stddev;

	t_linked_list	*li; // to free
}	t_ping_list;

extern volatile t_ping_list list;

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, char *src);
void	free_list();
void	error_and_exit(char *str);

void	ft_parsing(int ac, char **av);
void	ft_check_hostname(struct sockaddr_in *addr_hostname);

void 	ft_ping();

long double		ft_pow(long double nbr);
double 			ft_sqrt(float x);
float 			ft_avg(int len);
float			ft_stddev(int len);
float 			ft_min();
float 			ft_max();

void	free_li();
void	add_end(float new);

#endif
