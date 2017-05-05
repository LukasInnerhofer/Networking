#include "client.h"

int main()
{
	char buffer[256];
	memset(buffer, '-', sizeof(buffer));
	strcpy(buffer, "Hello World");
	networking::verbose = true;
	networking::initClient(5000, AF_INET, SOCK_STREAM);
	char address[10] = "127.0.0.1";
	networking::connectToServer(address);
	networking::writeToServer(buffer, sizeof(buffer));
	return 0;
}
