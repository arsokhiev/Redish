#include "Server.h"

int main(int argc, char** argv)
{
	Redish::Log::init();
	rd_info("Server Logger has been initialized\n");

	if (argc != 3)
	{
		rd_critical("Args port and maximum_number_of_clients must be entered");
		exit(1);
	}
		
	Redish::Server server("127.0.0.1", atoi(argv[1]), atoi(argv[2]));
	server.start();

	return 0;
}