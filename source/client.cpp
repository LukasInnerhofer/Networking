#include "client.h"

namespace networking
{
	bool verbose = false;

	struct sockaddr_in address;
	int socketFD;

	int initClient(const uint16_t port, const int family, const int protocol)
	{
		socketFD = socket(family, protocol, 0);
		if(socketFD < 0)
		{
			if(verbose)
				std::cerr << "\nError opening socket: " << strerror(errno) << std::endl;
			return errno;
		}

		memset(&address, '0', sizeof(address));

		address.sin_family = family;
		address.sin_port = htons(port);
		
		return 0;
	}

	int connectToServer(char serverAddress[])
	{
		if(inet_pton(address.sin_family, serverAddress, &address.sin_addr) <= 0)
		{
			if(verbose)
				std::cerr << "\nError reading server address: " << strerror(errno) << std::endl;
			return errno;
		}

		if(connect(socketFD, (struct sockaddr *)&address, sizeof(address)) < 0)
		{
			if(verbose)
				std::cerr << "\nError connecting to server: " << strerror(errno) << std::endl;
			return errno;
		}

		return 0;
	}

	int writeToServer(char buffer[])
	{
		if(write(socketFD, buffer, sizeof(buffer) - 1) < 0)
		{
			if(verbose)
				std::cerr << "\nError writing to server: " << strerror(errno) << std::endl;
			return errno;
		}

		return 0;
	}
}
