#include "../h/ft_ping.h"

// volatile t_ping_list list;

unsigned short ft_checksum(void *ele, int len)
{
	unsigned short	*buf = (unsigned short *)ele;
	unsigned short	res = 0;
	unsigned int	sum = 0;

	while (len > 1)
	{
		sum += *buf++;
		len -= 2;
	}
	if (len == 1)
		sum += *(unsigned char *)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	res = (unsigned short)~sum;
	return (res);
} 

void ft_ping()
{
	// packet creation, init of variables
	struct timeval			t_time_out;
	t_time_out.tv_sec = 1; // Time out set to one sec
	t_time_out.tv_usec = 0;

	struct timeval p_start, p_end;

	// setting the options of the sockets for sending.
    // Doc="The TCP/IP specification states that the TTL field for TCP packets should be set to 60"
	int ttl = 60;
	if (setsockopt(list.fd, SOL_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
	{
		if (list.verbose)
			printf(RED "[ERROR] " RESET "An error occurred with the TTL option setting\n");
		error_and_exit("setsockopt IP_TTL");
	}
	if (setsockopt(list.fd, SOL_SOCKET, SO_RCVTIMEO, &t_time_out, sizeof(t_time_out)) < 0)
	{
		if (list.verbose)
			printf(RED "[ERROR] " RESET "An error occurred with the socket timeout option setting\n");
		error_and_exit("setsockopt SO_RCVTIMEO");
	}

	// sending the ping requests (icmp packets) continuously
	bool sended;
	list.msg_sended = 0;
	list.msg_received = 0;

	printf("PING %s (%s): %d data bytes\n", list.hostname, list.ip, PACKET_SIZE);

	while (1)
    {
        sended = true;
        char send_pckt[PACKET_SIZE];
        char res[PACKET_SIZE + sizeof(struct ip)];  // Allocate enough space for IP header + ICMP
        struct sockaddr_storage sender;
        socklen_t sender_len = sizeof(sender);

        memset(send_pckt, 0, sizeof(send_pckt));

        struct icmphdr *icmph = (struct icmphdr *)send_pckt;
        icmph->type = ICMP_ECHO;
        icmph->code = 0;
        icmph->un.echo.id = getpid();
        icmph->un.echo.sequence = list.msg_sended;
        icmph->checksum = ft_checksum(send_pckt, PACKET_SIZE);

        usleep(1000000);

        gettimeofday(&p_start, NULL);

        if (sendto(list.fd, send_pckt, PACKET_SIZE, 0, (struct sockaddr *)&list.addr_hostname, sizeof(list.addr_hostname)) <= 0)
        {
        	fprintf(stderr, "ping: socket: %s\n", strerror(errno));
            sended = false;
        }
        else
            list.msg_sended += 1;        

        if (recvfrom(list.fd, res, sizeof(res), 0, (struct sockaddr *)&sender, &sender_len) <= 0 && list.msg_sended >= 1)
        {
            if (list.msg_sended >= 1)
            {
                if (list.verbose)
                {
                    // impossible de transmettre le pckt pour l'instant
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                        printf(RED "[ERROR] " RESET "Request timeout: No response received for packet %d.\n", list.msg_sended);
                    else
                        printf(RED "[ERROR] " RESET "Failed to receive a response for packet %d: %s.\n", list.msg_sended, strerror(errno));
                }
                else
                    printf("Request timeout for icmp_seq %d\n", (list.msg_sended - 1));
            }
        }
        else if (sended)
        {
            gettimeofday(&p_end, NULL);

            double ping_time = ((double)(p_end.tv_usec - p_start.tv_usec) / 1000);
            long double total_ping_time = (long double)(((p_end.tv_sec - p_start.tv_sec) * 1000) + ping_time);

            struct ip *ip_hdr = (struct ip *)res;
            int ip_hdr_len = ip_hdr->ip_hl * 4;
            struct icmphdr *recv_icmph = (struct icmphdr *)(res + ip_hdr_len);

            if (recv_icmph->type == ICMP_ECHOREPLY && recv_icmph->code == 0)
            {
                printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", ttl, list.ip, recv_icmph->un.echo.sequence, ttl, (float)total_ping_time);
				add_end(total_ping_time);
                list.msg_received++;
            }
            else if (recv_icmph->type != ICMP_ECHOREPLY || recv_icmph->code != 0)
            {
                if (list.verbose)
                    printf(GREEN "\n[VERBOSE] " RESET "Received ICMP message: type=%d, code=%d\n", recv_icmph->type, recv_icmph->code);
                if (recv_icmph->type == ICMP_DEST_UNREACH)
                    printf("From %s: Destination Unreachable\n", list.ip);
                else if (recv_icmph->type == ICMP_TIME_EXCEEDED)
                    printf("From %s: Time to live exceeded\n", list.ip);
            }
        }
    }
}
