#include "Client.h"

Redish::Client::Client(int port, std::string ip_address) :
	wsa_data{ 0 },
	client_socket(INVALID_SOCKET),
	destination_address{ 0 },
	ip_address(ip_address),
	port(port),
	destination_address_length(sizeof(destination_address))
{}

Redish::Client::~Client()
{
	// todo
}

void Redish::Client::connect()
{
	init();

	rd_debug("Try connect to server");
	if (::connect(client_socket, (sockaddr*)&destination_address, destination_address_length) != 0)
	{
		rd_critical("Couldn`t connect to server");
	}
	rd_info("Connected to: {}:{}", inet_ntoa(destination_address.sin_addr), ntohs(destination_address.sin_port));

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_handler, (LPVOID)(this), NULL, NULL);

	while (true)
	{
		std::getline(std::cin, message);
		int message_size = message.size();

		send(client_socket, (const char*)&message_size, sizeof(int), NULL);
		send(client_socket, message.c_str(), message_size, NULL);
	}
}

void Redish::Client::init()
{
	destination_address.sin_family = AF_INET;
	destination_address.sin_port = htons(port);
	destination_address.sin_addr.S_un.S_addr = inet_addr(ip_address.c_str());

	rd_debug("WSA init");
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
	{
		rd_critical("Couldn`t init wsa");
		exit(WSAGetLastError());
	}
	rd_info("WSA success\n");

	rd_debug("Creating Client Socket");
	if ((client_socket = socket(AF_INET, SOCK_STREAM, NULL)) == SOCKET_ERROR)
	{
		rd_critical("Couldn`t create socket");
		exit(WSAGetLastError());
	}
	rd_info("Success\n");
}

void Redish::client_handler(Client& client)
{
	int recieved_message_size;
	while (true)
	{
		//recv(client_socket, const_cast<char*>(recieved_message.c_str()), rm_size, 0);
		recv(client.client_socket, (char*)&recieved_message_size, sizeof(int), NULL);

		char* recieved_message = new char[recieved_message_size + 1];
		recieved_message[recieved_message_size] = '\0';

		recv(client.client_socket, recieved_message, recieved_message_size, NULL);

		//printf("%s\n", recieved_message);
		rd_debug("{}", recieved_message);
		//std::cout << ">>" << recieved_message << std::endl;

		delete[] recieved_message;
	}
}
