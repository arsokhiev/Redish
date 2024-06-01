#pragma once

#include <iostream>
#include <iomanip>
#include <ranges>
#include <string_view>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <WinSock2.h>

#include "ServerLog.h"
#include "Utils.h"

#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRICATED_NO_WARNINGS
#pragma warning(disable: 4996)

namespace Redish
{

	struct Handle_params;

	class Server
	{
	private:
		WSADATA wsa_data;
		SOCKET listen_socket;
		sockaddr_in socket_address;
		std::string ip_address;
		int port;
		std::string message;
		int socket_address_length;
		int recv_length;

		const int max_connections;

		std::list<SOCKET> connections;
		std::unordered_map<std::string, std::string> data;

	public:
		Server(int port, std::string ip_address, int max_connections);
		~Server();

	public:
		void start();

	private:
		void init();

		int accept_connection(SOCKET& write_into);
		void add_connection(const SOCKET& new_connection);
		void del_connection();

		friend void client_handler(Handle_params h_params);

		static std::string put(std::unordered_map<std::string, std::string>& data,
			std::pair<std::string, std::string> pair);

		static std::string get(std::unordered_map<std::string, std::string>& data, 
			std::string key);

		static std::string del(std::unordered_map<std::string, std::string>& data, 
			std::string key);

		static std::string count(std::unordered_map<std::string, std::string>& data) 
		{ return std::to_string(data.size()); };
	};

	struct Handle_params
	{
		SOCKET current_connection;
		Redish::Server& server;

		Handle_params(SOCKET connection, Redish::Server& server) :
			current_connection(connection),
			server(server) {}
	};

	void client_handler(Handle_params h_params);

}

