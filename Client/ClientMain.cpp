#include "Client.h"

int main(int argc, char** argv)
{
	Redish::Log::init();
	rd_info("Client Logger has been initialized\n");

	if (argc != 2)
	{
		rd_critical("Port must be entered");
		exit(1);
	}
	Redish::Client client("127.0.0.1", atoi(argv[1]));
	client.connect();

	return 0;
}