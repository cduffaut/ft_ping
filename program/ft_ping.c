#include "../h/ft_ping.h"

volatile t_ping_list list;

void	free_list()
{
	free_li();
	if (list.ip)
		free (list.ip);
	if (list.fd)
		close (list.fd);
}

static void control_c()
{
	float percentage_loss = ((float)(list.msg_sended - list.msg_received) / (float)list.msg_sended) * 100;
	// set the end time of the entire ping process
	
	if (list.li)
	{
		list.max = ft_max();
		list.min = ft_min();
		list.avg = ft_avg(list.msg_received);
		list.stddev = ft_stddev(list.msg_received);
	}
	printf ("\n--- %s ping statistics ---\n", list.hostname);
	printf("%d packets transmitted, %d packets received, %.1f%% packet loss\n",
	       list.msg_sended, list.msg_received, percentage_loss);
	if (list.msg_received > 0)
	{
		printf ("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", list.min, list.avg, list.max, list.stddev);
	}
	free_list();
	exit (0);
}

static void to_null()
{
	list.ip = NULL;
	list.li = NULL;
	list.verbose = false;
}

int main (int argc, char **argv)
{
	if (getuid() != 0)
		error_and_exit ("Error\nYou're not in root mode, the program cannot run without root permissions.");
	to_null();
	list.len_addr_hostname = sizeof(list.addr_hostname);

	signal(SIGINT, control_c);
	// Première partie de parsing: verif des options, et nbr d'args.
	ft_parsing(argc, argv);

	// Deuxième partie de parsing: verif du hostname saisit en input.
	ft_check_hostname((struct sockaddr_in *)&list.addr_hostname);
	if (!list.ip)
		{ printf ("ping: cannot resolve %s: Unknown host\n", list.hostname); return (0); }

	// Socket creation
	// (IPPROTO_)ICMP est le protocole utilisé par la commande ping pour envoyer 
	// des requêtes de type "echo request" et recevoir des réponses de type "echo reply"
	list.fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (list.fd < 0)
	{
    	fprintf(stderr, "ping: socket: %s\n", strerror(errno));
    	error_and_exit("");
	}
	ft_ping();
	free_list();
	return (0);
}
