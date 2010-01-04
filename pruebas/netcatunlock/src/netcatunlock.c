/*
 ============================================================================
 Name        : netcatunlock.c
 Author      : tuareg,ojcchar
 Version     : 0.1
 Copyright   : copyright UNLock
 Description : mini netcat
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

	//Se verifica el numero de argumentos
	if (argc < 3) {
		printUsage();
		return EXIT_SUCCESS;
	}

	puts("These are the arguments:");
	for (var = 1; var < argc; ++var) {
		puts(argv[var]);
	}

	//se obtiene la direccion y el puerto si son validos
	addrPort ap = getAddressPort(argv[1], argv[2]);

	//se crea el socket de tipo stream y con el namespace de internet
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		puts("Could not create the socket");
		exit(EXIT_FAILURE);
	}

	//se crea la estructura sockaddr_in para realizar la conexion
	struct sockaddr_in rem_addr;
	memset(&rem_addr, 0, sizeof(rem_addr)); //se pone en cero
	rem_addr.sin_family = AF_INET; //la familia de direcciones de internet IPv4
	rem_addr.sin_port = ap.port; //se fija el puerto
	memcpy(&rem_addr.sin_addr, &ap.inAdd, sizeof(rem_addr.sin_addr)); //se fija la direccion

	//se realiza la conexion
	if (connect(sock, (struct sockaddr *) &rem_addr, sizeof(rem_addr)) < 0) {
		puts("Could not connect to the host");
		exit(EXIT_FAILURE);
	}else
		puts("Connection was successful");

	//se cierra el sockets
	if ((shutdown(sock, 0) < 0) ) {
		puts("Could not shutdown the sockets");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

addrPort getAddressPort(char *addr, char *port) {
	struct in_addr *inAdd;
	memset(&inAdd,0,sizeof(inAdd));

	//se obtiene la direccion en in_addr
	int ret = inet_aton(addr, inAdd);
	if (!ret) {
		puts("Address is not valid");
		exit(EXIT_FAILURE);
	}

	char **endptr;
	memset(&endptr,0,sizeof(endptr));

	//se obtiene el puerto del string y se verifica
	long por = strtol(port, endptr, 10);
	if ((por < 0) || (por > 65536)) {
		puts("Port is not valid");
		exit(EXIT_FAILURE);
	}

	addrPort ap;
	ap.inAdd = inAdd;
	//se obtiene el puerto de acuerdo a la ordenacion de bits de linux
	ap.port = htons(por);
	return ap;

}

void printUsage() {
	puts("Usage: netcatunlock host port");

}

