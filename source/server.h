#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <errno.h>

namespace networking
{
	extern bool verbose;

	extern int socketFD, newSocketFD;
	extern socklen_t clientLength;
	
	extern struct sockaddr_in serverAddress, clientAddress;

	int initServer(uint16_t port, int family, int protocol);
	int acceptConnection();
	int readFromClient(char buffer[]);
}

#endif //SERVER_H
