#include "server.h"
#include <iostream>

int main()
{
	char buffer[256];
	networking::verbose = true;
	networking::initServer(5000, AF_INET, SOCK_STREAM);
	while(true)
	{
		networking::acceptConnection();
		networking::readFromClient(buffer, sizeof(buffer));
		std::cout << buffer;
		std::cout << std::endl;
	}
}
