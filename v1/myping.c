#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


static void testFunc(const char *host);

void testFunc(const char *host){
	// 1. Define Hints:
		
	struct addrinfo hints = {
		0,		// ai_flags
		AF_INET,	// ai_family
		0,		// ai_socktype
		IPPROTO_ICMP,	// ai_protocol
		0,		// ai_addrlen
		NULL, 		// *ai_addr
		NULL,		// *ai_canonname
		NULL		// *ai_next
	};

	// 2. Declare a pointer to a strucutre which
	// will have the address of whatever getaddrinfo returns

	struct addrinfo *pAddrinfo;
	
	// 3. CALL THE function getaddrinfo , print
	// returned values and quit 

	int retValue = getaddrinfo(host, NULL, NULL,&pAddrinfo);
	if (retValue != 0) {
		fprintf(stderr,"Error from getaddrinfo %s\n",gai_strerror(retValue));
		exit(1);
	} else {		
	   fprintf(stdout,"Return Value is: %d\n", retValue);
	   while (pAddrinfo != NULL) {
	   	fprintf(stdout, "Flags %x, socktype %d, protocol %d, address length %d, canonical name %s socket data %s\n",
				  pAddrinfo->ai_flags, pAddrinfo->ai_socktype, pAddrinfo->ai_protocol, pAddrinfo->ai_addrlen,
	   			  pAddrinfo->ai_canonname, pAddrinfo->ai_addr->sa_data);
	   	pAddrinfo = pAddrinfo->ai_next;
	   }
	}
}


int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s hostname\n",argv[0]);
	
	} else {
		testFunc(argv[1]);
	}

	return 0;
	
}
