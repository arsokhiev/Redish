#include "Server.h"

Redish::Server::Server(std::string ip_address, int port, int max_connections) :
	wsa_data{ 0 },
	listen_socket(INVALID_SOCKET),
	socket_address{ 0 },
	ip_address(ip_address),
	port(port),
	socket_address_length(sizeof(socket_address)),
	max_connections(max_connections)
{}

Redish::Server::~Server()
{
	WSACleanup();

	for (auto connection : connections)
	{
		closesocket(connection);
	}

	closesocket(listen_socket);
}

void Redish::Server::start()
{
	init();

	listen(listen_socket, SOMAXCONN);

	SOCKET new_connection;
	while (true)
	{
		if (connections.size() >= max_connections)
		{
			Sleep(300);
			continue;
		}

		if (accept_connection(new_connection))
		{
			add_connection(new_connection);

			Handle_params handle_params(new_connection, *this);

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_handler, (LPVOID)(&handle_params), NULL, NULL);
		}
	}
}

void Redish::Server::init()
{
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = htons(port);
	socket_address.sin_addr.s_addr = inet_addr(ip_address.c_str());

	rd_debug("WSA init");
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
	{
		rd_critical("Couldn`t init wsa");
	}
	rd_info("WSA success\n");

	rd_debug("Creating Server Socket");
	if ((listen_socket = socket(AF_INET, SOCK_STREAM, NULL)) == SOCKET_ERROR)
	{
		rd_critical("Couldn`t create socket");
	}
	rd_info("Server Socket was succesfully created\n");

	rd_debug("Binding socket");
	if (bind(listen_socket, (SOCKADDR*)&socket_address, socket_address_length))
	{
		rd_critical("Couldn`t bind socket");
	}
	rd_info("Bocket binded\n");

	rd_info("Server started at: {}:{}\n", inet_ntoa(socket_address.sin_addr), ntohs(socket_address.sin_port));
}

void Redish::Server::add_connection(const SOCKET& new_connection)
{
	connections.push_back(new_connection);
	rd_debug("new socket was added to connections\n");
}

void Redish::Server::del_connection(SOCKET& del_connection)
{
	connections.remove_if([del_connection](SOCKET connection)
		{
			return connection == del_connection;
		});
	rd_debug("socket was deleted from connections\n");
}

int Redish::Server::accept_connection(SOCKET& write_into)
{
	write_into = accept(listen_socket, (SOCKADDR*)&socket_address, &socket_address_length);

	if (write_into == INVALID_SOCKET)
	{
		rd_critical("{}", WSAGetLastError());
		rd_warn("failed connection attempt");
		return 0;
	}
	else
	{
		rd_debug("new client connected");
		std::string accept_message = "Accepted by the server";
		int message_size = accept_message.size();

		send(write_into, (char*)&message_size, sizeof(int), NULL);
		send(write_into, accept_message.c_str(), message_size, 0);

		return 1;
	}
}

void Redish::client_handler(Redish::Handle_params h_params)
{
	while (true)
	{
		std::string client_command;
		Server::recieve_from_client(h_params.current_connection, client_command);

		std::list<std::string> recognised_words;
		Utils::recognise_words(client_command, recognised_words);

		if (recognised_words.size() < 1)
		{
			rd_warn("incorrect request entered");
			continue;
		}

		Utils::ECommands recognised_command = Utils::recognise_command(recognised_words.front().c_str());
		recognised_words.pop_front();

		std::string result;
		Server::operate(h_params.server, recognised_command, recognised_words, result);

		Server::send_to_client(h_params.current_connection, result);
	}
}

void Redish::Server::recieve_from_client(SOCKET connection, std::string& return_client_command)
{
	int client_command_size;
	char* client_command;

	recv(connection, (char*)&client_command_size, sizeof(int), NULL);

	client_command = new char[client_command_size + 1];
	client_command[client_command_size] = '\0';

	recv(connection, client_command, client_command_size, NULL);

	return_client_command = client_command;

	delete[] client_command;
}

void Redish::Server::send_to_client(SOCKET connection, std::string& sendable)
{
	int sendable_size = sendable.size();
	send(connection, (const char*)&sendable_size, sizeof(int), NULL);
	send(connection, sendable.c_str(), sendable_size, NULL);
}

void Redish::Server::operate(Server& server, Utils::ECommands command, std::list<std::string>& recognised_words, std::string& result)
{
	switch (command)
	{
	case Utils::ECommands::PUT:
		if (Utils::check_command_argc(recognised_words, 2))
		{
			result = server.put(server.data, std::make_pair(recognised_words.front().c_str(),
				recognised_words.back().c_str()));
			break;
		}
		result = "The PUT command should take 2 arguments";
		break;

	case Utils::ECommands::GET:
		if (Utils::check_command_argc(recognised_words, 1))
		{
			result = server.get(server.data, recognised_words.front().c_str());
			break;
		}
		result = "The GET command should take 1 argument";
		break;

	case Utils::ECommands::DEL:
		if (Utils::check_command_argc(recognised_words, 1))
		{
			result = server.del(server.data, recognised_words.front().c_str());
			break;
		}
		result = "The DEL command should take 1 argument";
		break;

	case Utils::ECommands::COUNT:
		if (Utils::check_command_argc(recognised_words, 0))
		{
			result = server.count(server.data);
			break;
		}
		result = "The COUNT command should be called without any arguments";
		break;

	case Utils::ECommands::NOT_RECOGNISED:
	default:
		rd_warn("A non-existent command was entered");
		result = "Incorrect command entered. Try again";
		break;
	}
}

std::string Redish::Server::put(std::unordered_map<std::string, std::string>& data,
	std::pair<std::string, std::string> pair)
{
	if (auto search = data.find(pair.first); search != data.end())
	{
		std::string result = "OK ";
		result.append(search->second);

		search->second = pair.second;

		return result;
	}
	else
	{
		data.insert(pair);
		return "OK";
	}
}

std::string Redish::Server::get(std::unordered_map<std::string, std::string>& data,
	std::string key)
{
	if (auto search = data.find(key); search != data.end())
	{
		std::string result = "OK ";
		result.append(search->second);
		return search->second;
	}
	else
	{
		return "NE";
	}
}

std::string Redish::Server::del(std::unordered_map<std::string, std::string>& data,
	std::string key)
{
	if (auto search = data.find(key); search != data.end())
	{
		std::string result = "OK ";
		result.append(search->second);

		data.erase(key);

		return result;
	}
	else
	{
		return "NE";
	}
}