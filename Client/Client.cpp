#include "Client.h"

Redish::Client::Client(std::string ip_address, int port = 8888) :
	wsa_data{ 0 },
	client_socket(INVALID_SOCKET),
	destination_address{ 0 },
	ip_address(ip_address),
	port(port),
	destination_address_length(sizeof(destination_address))
{}

Redish::Client::~Client()
{
	closesocket(client_socket);
}

void Redish::Client::connect()
{
	init();

	rd_debug("Try connect to server");
	if (::connect(client_socket, (sockaddr*)&destination_address, destination_address_length) != 0)
	{
		rd_critical("Couldn`t connect to server");
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_handler, (LPVOID)(this), NULL, NULL);

	Sleep(300);
	rd_info("Connected to: {}:{}", inet_ntoa(destination_address.sin_addr), ntohs(destination_address.sin_port));

	while (true)
	{
		std::getline(std::cin, message);
		send_to_server(message);
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

void Redish::Client::recieve_from_server()
{
	int recieved_message_size;
	char* recieved_message;

	recv(client_socket, (char*)&recieved_message_size, sizeof(int), NULL);

	recieved_message = new char[recieved_message_size + 1];
	recieved_message[recieved_message_size] = '\0';

	recv(client_socket, recieved_message, recieved_message_size, NULL);

	rd_debug("{}", recieved_message);

	delete[] recieved_message;
}

void Redish::Client::send_to_server(std::string& sendable)
{
	int sendable_size = sendable.size();
	send(client_socket, (const char*)&sendable_size, sizeof(int), NULL);
	send(client_socket, sendable.c_str(), sendable_size, NULL);
}

void Redish::client_handler(Client& client)
{
	int recieved_message_size;
	while (true)
	{
		client.recieve_from_server();
	}
}
