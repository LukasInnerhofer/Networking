#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <iostream>
#include <exception>
#include <cstring>
#include <unistd.h>
#include <errno.h>

namespace networking
{
	extern bool verbose;

	extern struct sockaddr_in address;
	extern int socketFD;

	int initClient(uint16_t port, int family, int protocol);
	int connectToServer(char serverAddress[]);
	int writeToServer(char buffer[]);
}

#endif //CLIENT_H
