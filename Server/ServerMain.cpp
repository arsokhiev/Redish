#include "Server.h"

int main(int argc, char** argv)
{
	Redish::Log::init();
	rd_info("Server Logger has been initialized\n");

	// проверка на кол-во аргументов

	// change to enter from user
	//Redish::Server server(atoi(argv[1]), "127.0.0.1", atoi(argv[2]));
	Redish::Server server(8888, "127.0.0.1", 10);
	server.start();

	return 0;
}