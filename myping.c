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
	
	// 3. Call the function getaddrinfo , print
	// returned values and quit 

	int retValue = getaddrinfo(host, "icmp", &hints,&pAddrinfo);
	if (retValue != 0) {
		fprintf(stderr,"Error from getaddrinfo %s\n",gai_strerror(retValue));
		exit(1);
	} else {		
	   fprintf(stdout,"Return Value is: %d", retValue);
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
