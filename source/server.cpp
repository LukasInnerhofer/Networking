#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
		int socket_fd, newsocket_fd, message_length;
		socklen_t client_length;
		uint16_t port;
		char buffer[256];

		struct sockaddr_in server_address, client_address;

		if(argc != 2)
		{
			std::cerr << "\nUsage: " << argv[0] << " <server port>\n";
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
			std::cerr << "\nError opening socket\n";
			return 1;
		}

		std::memset((char *)&server_address, '0', sizeof(server_address));

		server_address.sin_family = AF_INET;
		server_address.sin_port = htons(port);
		server_address.sin_addr.s_addr = INADDR_ANY;
		

		if(bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
		{
			std::cerr << "\nError trying to bind server to socket: " << errno;
			return 1;
		}	

		listen(socket_fd, 5);

		client_length = sizeof(client_address);
		while(true)
		{	
			newsocket_fd = accept(socket_fd, (struct sockaddr *)&client_address, &client_length);
			if(newsocket_fd < 0)
			{
				std::cerr << "\nError trying to accept a connection.\n";
				return 1;
			}
		
			std::memset(&buffer, '0', sizeof(buffer));
			message_length = read(newsocket_fd, buffer, sizeof(buffer) - 1);
			if(message_length < 0)
			{
				std::cerr << "\nError reading from socket\n";
				return 1;
			}
		
			std::cout << std::endl << buffer << std::endl;
		}
		
		return 0;
}

		
