#include "../h/ft_ping.h"

// volatile t_ping_list list;

static void display_help()
{
	printf ("Usage: ft_ping [options] <destination>\nOptions:\n\t-v\tVerbose output\n\t-?\tDisplay this help message\n");
	exit (0);
}

// DNS lookup: is the process through which human-readable domain names (www.digicert.com) are 
// translated into a computer-readable IP address (216.168.246.55).
void	ft_check_hostname(struct sockaddr_in *addr_hostname)
{
	struct hostent	*data_hostname;
	list.ip = (char *)malloc(sizeof(char) * ft_strlen((const char *)list.hostname));
	
	if (!list.ip)
		error_and_exit("Error: memory allocation failed for hostname\n");

	data_hostname = gethostbyname(list.hostname);
	if (!data_hostname)
		{free (list.ip); list.ip = NULL; return;}
	// h_addr est un pointeur vers une adresse IP en format binaire (tableau d'octets qui représente l'adresse IP.)
	// inet_ntoa prend une structure (qui contient l'adresse IP en format binaire) et retourne sous forme de str type 127.0.0.1
	/*struct in_addr
	{ unsigned long s_addr;  // load with inet_aton() };*/
	ft_strcpy(list.ip, inet_ntoa(*(struct in_addr *)data_hostname->h_addr));
	(*addr_hostname).sin_family = data_hostname->h_addrtype;
	(*addr_hostname).sin_port = htons(NO_PORT);
	// assignation de l'ip sous forme binaire à s_addr qui elle aussi prend une IP en binaire
	(*addr_hostname).sin_addr.s_addr = *(in_addr_t *)data_hostname->h_addr;
}

void	ft_parsing(int ac, char **av)
{
	if (ac <= 1)
		error_and_exit("Error: Wrong number of arguments.\nPlease respect the format ping [-v?] [ip/hostname]\n");
	if (!ft_strcmp(av[1], "-?") && ac <= 3)
		display_help();
	if (ac == 3)
	{
		if (ft_strcmp(av[1], "-?") && ft_strcmp(av[1], "-v"))
		{
			if (ft_strlen(av[1]) > 1)
				printf ("ping: invalid option -- %c\n", av[1][2]);
			else
				printf ("ping: invalid option -- %s\n", av[1]);
			error_and_exit("Usage: ft_ping [options] <destination>\nOptions:\n\t-v\tVerbose output\n\t-?\tDisplay this help message\n");
		}
		if (!ft_strcmp(av[1], "-v"))
			list.verbose = true;
	}
	if (list.verbose)
		list.hostname = av[2];
	else if (ac == 2)
		list.hostname = av[1];
	else
		error_and_exit("Error: Wrong number of arguments.\nPlease respect the format ping [-v?] [ip/hostname]\n");
}