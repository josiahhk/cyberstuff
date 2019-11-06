/*
spoof.c

Spoofs a UDP packet. If you want to change the IP addresses, you have
to do it in the code.

*/

#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

//taken from rawip.txt
unsigned short	csum (unsigned short *buf, int nwords)
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
	//Create a raw socket with UDP protocol
	sd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
	if(sd < 0){
		perror("socket() error"); 
		exit(-1);
	}
	
	sin.sin_family=AF_INET;
	sin.sin_port = htons (53);
	sin.sin_addr.s_addr = inet_addr ("216.58.217.196");

	char buffer[4096];
	memset(buffer, 0, 4096);
	struct ip *ip = (struct ip*) buffer;
	struct udphdr *udp = (struct udphdr*)(buffer + sizeof(ip));
	const int on = 1;

	ip->ip_hl = 5;
	ip->ip_v = 4;
	ip->ip_tos = 0;
	ip->ip_len = sizeof(struct ip) + sizeof(struct udphdr); 
	ip->ip_id = htons(54321);
	ip->ip_off = 0;
	ip->ip_ttl = 255;
	ip->ip_p = 17;
	ip->ip_sum = 0;
	ip->ip_src.s_addr = inet_addr("123.45.67.8");
	ip->ip_dst.s_addr = inet_addr("216.58.217.196");
	ip->ip_sum =csum((unsigned short *)buffer, sizeof(struct ip) + sizeof(struct udphdr));

	udp->uh_sport = htons(45512);
	udp->uh_dport = htons(53);
 	udp->uh_ulen = htons(sizeof(struct udphdr));
 	udp->uh_sum = 0;

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
