/*
 *  Specify to the compiler the set of features we want.
 *  Here needed for 'struct addr'.
 */
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>

// getaddrinfo...
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

#define REQUEST_MAX 1024	// Max size of a request
#define ACTIONS_MAX 1		// "GET", "DELETE"... 
#define METHODS_MAX 32		// "StartNewGame", "SelectCell"...
#define ARGS_MAX	32

int parseRequest(char* request) {
	char *action = malloc(ACTIONS_MAX*sizeof(char));
	char *token = strtok(request, " ");

	if (token != NULL) strcpy(action, token);
	else {
		free(token);	
		return 1;
	}

	fprintf(stderr,"%s\n", action);

	free(action);
	return 0;
}

int treatRequest(char* request) {
	parseRequest(request);

	return 0;
}

int startServer(char* port) {
	int s,		// Server socket file descriptor
	    sock,	// Client socket file descriptor
	    ret;	// Functions return

	struct addrinfo hints,		// Our TCP server caracteritics
					*result;	// Our actual TCP server address

	struct sockaddr_storage src_addr;
	socklen_t len_src_addr;
	char request[REQUEST_MAX];	// Data of client requests

	// Fill memory at 'hints' address with 0
	memset(&hints, 0, sizeof(struct addrinfo)); 

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET6;			// Allow IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;	// Define TCP stream
	hints.ai_protocol = 0;				// Allow any protocol
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	
	// Build our TCP server address
	ret = getaddrinfo(NULL, port, &hints, &result);
	
	if(ret != 0) {
		fprintf(stderr, "Error getaddrinfo: %s.\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}

	// Create the IP socket
	if((s=socket(result->ai_family, result->ai_socktype, 
					result->ai_protocol)) == -1) {
		perror("socket");
		exit(1);
	}

	// Bind the socket to a local address
	if(bind(s, result->ai_addr, result->ai_addrlen) == -1 ) {
		perror("bind");
		exit(1);
	}

	// The socket is created, we can free the address informations
	freeaddrinfo(result);

	// Limit the queue of incoming connections
	if(listen(s,5)) {
		perror("listen");
		exit(1);
	}

	// Server execution loop
	while(1) {
		puts("Waiting for connection...");
		
		len_src_addr = sizeof src_addr;

		// Wait for new connection and accept it
		if((sock=accept(s, (struct sockaddr *)&src_addr, 
						&len_src_addr)) == -1) {
			perror("accept");
			exit(1);
		}

		puts("New connection accepted.");

		// Wait for new request received
		while((ret=recv(sock, request, REQUEST_MAX, 0)) > 0) {
			// Add end-string caracter at the end of the request
			request[ret] = 0;
			
			// region: Treatment
			puts("Treatment in progress.");
			treatRequest(request);
			// endregion : Treatment
			
			// Send response
			if(send(sock, request, strlen(request)+1, 0) 
					!= strlen(request)+1) {
				perror("send");
				exit(1);
			}
		}

		// Close connexion
		if(close(sock) == -1) {
			perror("close");
			exit(1);
		}
		fprintf(stderr, "Connexion ended.\n");

		if(ret == -1) perror("recv");
	}

	return 0;
}

/*
 *  Accept one argument which identify the service we are using.
 */
int main(int argc, char* argv[]) {
	if(argc != 2) {
		fprintf(stderr,"Error: arguments number.\n");
		exit(1);
	}

	startServer(argv[1]);

	return 0;
}
