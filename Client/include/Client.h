#pragma once

#include <iostream>
#include <string>
#include <WinSock2.h>

#include "ClientLog.h"

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRICATED_NO_WARNINGS
#pragma warning(disable: 4996)

namespace Redish
{

	class Client
	{
	private:
		WSADATA wsa_data;
		SOCKET client_socket;
		sockaddr_in destination_address;
		std::string ip_address;
		int port;
		std::string message;
		int destination_address_length;
		int recv_length;

		friend class Server;

	public:
		Client(std::string ip_address, int port);
		~Client();

	public:
		void connect();

	private:
		void init();

		void recieve_from_server();
		void send_to_server(std::string& sendable);

		friend void client_handler(Client& client);
	};

	void client_handler(Client& client);

}