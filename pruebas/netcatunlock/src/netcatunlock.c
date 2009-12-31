/*
 ============================================================================
 Name        : netcatunlock.c
 Author      : tuareg,ojcchar
 Version     :
 Copyright   : copyright UNLock
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

typedef struct addrPort {
	struct in_addr *inAdd;
	in_port_t port;
} addrPort;

void printUsage();
addrPort getAddressPort(char *addr, char *port);

int main(int argc, char *argv[]) {
	short var;

	if (argc < 3) {
		printUsage();
		return EXIT_SUCCESS;
	}

	puts("These are the arguments:");
	//puts((const char )argc);
	for (var = 1; var < argc; ++var) {
		//puts((char)var);
		puts(argv[var]);
	}

	addrPort ap = getAddressPort(argv[1], argv[2]);

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		puts("Could not create the socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in rem_addr;
	memset(&rem_addr, 0, sizeof(rem_addr));
	rem_addr.sin_family = AF_INET;
	rem_addr.sin_port = ap.port;
	memcpy(&rem_addr.sin_addr, ap.inAdd, sizeof(rem_addr.sin_addr));

	struct sockaddr * hh = (struct sockaddr *) &rem_addr;

	//int ret = connect(sock, hh, sizeof(rem_addr));
	/*if ((ret < 0) && (errno != EINPROGRESS)) {
	 puts("error.....");
	 exit(EXIT_FAILURE);
	 }
	 if (ret == -1) {
	 puts("Could not connect to the host");
	 exit(EXIT_FAILURE);
	 }
	 if (ret == 0) {
	 puts("Could connect to the host");
	 }
	 */
	//puts(resp);

	return EXIT_SUCCESS;
}

addrPort getAddressPort(char *addr, char *port) {
	struct in_addr *inAdd;
	int ret = inet_aton(addr, inAdd);
	if (!ret) {
		puts("Address is not valid");
		exit(EXIT_FAILURE);
	}

	char *endptr;
	long por = strtol(port, endptr, 10);

	if ((por < 0) || (por > 65536)) {
		puts("Port is not valid");
		exit(EXIT_FAILURE);
	}

	addrPort ap;
	ap.inAdd = inAdd;
	ap.port = (in_port_t) por;
	return ap;

}

void printUsage() {
	puts("Usage: netcatunlock host port");

}
