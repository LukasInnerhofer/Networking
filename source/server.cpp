#include "server.h"

namespace networking
{
	bool verbose = false;

	int socketFD, newSocketFD;
	socklen_t clientLength;
	
	struct sockaddr_in serverAddress, clientAddress;

	int initServer(uint16_t port, int family, int protocol)
	{
		socketFD = socket(family, protocol, 0);
		if(socketFD < 0)
		{
			if(verbose)
				std::cerr << "\nError opening socket: " << strerror(errno) << std::endl;
			return errno;
		}
		
		memset(&serverAddress, '0', sizeof(serverAddress));
	
		serverAddress.sin_family = family;
		serverAddress.sin_port = htons(port);
		serverAddress.sin_addr.s_addr = INADDR_ANY;

		if(bind(socketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		{
			if(verbose)
				std::cerr << "\nError binding socket: " << strerror(errno) << std::endl;
			return errno;
		}
		
		listen(socketFD, 5);
		
		clientLength = sizeof(clientAddress);

		return 0;
	}
	
	int acceptConnection()
	{
		newSocketFD = accept(socketFD, (struct sockaddr *)&clientAddress, &clientLength);
		if(newSocketFD < 0)
		{
			if(verbose)
				std::cerr << "\nError accepting connection: " << strerror(errno) << std::endl;
			return errno;
		}
		return 0;
	}

	int readFromClient(char buffer[], size_t length)
	{
		memset(buffer, '0', length);
		if(read(newSocketFD, buffer, length - 1) < 0)
		{
			if(verbose)
				std::cerr << "\nError reading from client: " << strerror(errno) << std::endl;
			return errno;
		}
		return 0;
	}
}
		
