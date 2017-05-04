#include "client.h"

namespace networking
{
	int initClient(uint16_t port, int family, int protocol)
	{
		socketFD = socket(family, protocol, 0);
		if(socketFD < 0)
		{
			return errno;
		}

		memset(&address, '0', sizeof(address));

		address.sin_family = family;
		address.sin_port = port;
		
		return 0;
	}

	int connectToServer(char serverIPAddress[])
	{
		if(inet_pton(address.sin_family, 
	}
}

int main(int argc, char *argv[])
{
	int socket_fd, port, message_length;
	struct sockaddr_in server_address;
	char buffer[256];

	if(argc < 3)
	{
		std::cerr << "\nUsage: " << argv[0] << " <client port> <server ip address>\n";
		return 1;
	}
	try
	{
		port = std::stoi(argv[1]);
	}
	catch(std::invalid_argument e)
	{
		std::cerr << "\nError reading port: " << e.what() << std::endl;
		return 1;
	}

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		std::cerr << "\nError creating socket: " << errno << std::endl;
		return 1;
	}
	
	memset(&server_address, '0', sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);

	if(inet_pton(AF_INET, argv[2], &server_address.sin_addr) <= 0)
	{
		std::cerr << "\nError reading server ip address: " << errno << std::endl;
		return 1;
	}

	if(connect(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		std::cerr << "\nError trying to connect to " << argv[2] << ": " << errno << std::endl;
		return 1;
	}
	
	buffer[0]='h';
	message_length = write(socket_fd, buffer, sizeof(buffer) - 1);
	if(message_length < 0)
	{
		std::cerr << "\nError trying to write to server: " << errno << std::endl;
		return 1;
	}
	
	return 0;
}
