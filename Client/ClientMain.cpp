#include "Client.h"

int main(int argc, char** argv)
{
	Redish::Log::init();
	rd_info("Client Logger has been initialized\n");

	// проверка на кол-во аргументов

	// change to enter from user
	//Redish::Server server(atoi(argv[1]), "127.0.0.1");
	Redish::Client client(8888, "127.0.0.1");
	client.connect();

	return 0;
}