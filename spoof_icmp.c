/*
spoof_icmp.c

Spoofs an ICMP echo request. If you want to change the IP addressed, you 
have to do it manually.
*/

#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>


unsigned short		
csum (unsigned short *buf, int nwords)
{
  unsigned long sum;
  for (sum = 0; nwords > 0; nwords--)
    sum += *buf++;
  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return ~sum;
}

int main(){


	int sd;
	struct sockaddr_in sin;
	sd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if(sd < 0){
		perror("socket() error"); 
		exit(-1);
	}
	
	sin.sin_family=AF_INET;
	sin.sin_port = htons (53);
	sin.sin_addr.s_addr = inet_addr ("216.58.217.196");
	//216.58.217.196
	char buffer[4096];
	memset(buffer, 0, 4096);
	struct ip *ip = (struct ip*) buffer;
	struct icmp *icmp = (struct icmp*)(buffer + sizeof(struct ip));

	ip->ip_hl = 5;
	ip->ip_v = 4;
	ip->ip_tos = 0;
	ip->ip_len = sizeof(struct ip) + sizeof(struct icmp);
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = 64;
	ip->ip_p = IPPROTO_ICMP;
	ip->ip_sum = 0;
	ip->ip_src.s_addr = inet_addr("10.0.2.15");
	ip->ip_dst.s_addr = inet_addr("216.58.217.196");
	ip->ip_sum = csum((unsigned short *)buffer, sizeof(struct ip) + sizeof(struct icmphdr));

	//int pid = getpid();
	/*
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
 	icmp->checksum = 0;
	icmp->checksum = csum((unsigned short *)&icmp, sizeof(icmphdr));
	*/

	icmp->icmp_type = 8;
  	icmp->icmp_code = 0;
  	icmp->icmp_id = htons(50179);
  	icmp->icmp_seq = htons(0x0);
  	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = 0xfc33;//csum((unsigned short *)&icmp, sizeof(struct icmp));
	//icmp->un.echo.id = rand();
	//icmp->un.echo.sequence = rand();

	//the below section seems to be critical in getting this to work
	{				
	int one = 1;
	const int *val = &one;
	if (setsockopt (sd, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
		printf ("Warning: Cannot set HDRINCL!\n");
	}
	//Send the crafted packet with raw socket
	if(sendto(sd, buffer, ip->ip_len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0){
		perror("sendto() error"); 
		exit(-1);
	
}
	printf("Reached the end without an error\n");

	return 0;

}
