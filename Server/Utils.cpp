#include "Utils.h"

const std::map<std::string, Utils::ECommands> Utils::mapping
{
	{"PUT",		ECommands::PUT},
	{"GET",		ECommands::GET},
	{"DEL",		ECommands::DEL},
	{"COUNT",	ECommands::COUNT}
};

bool Utils::check_command_argc(std::list<std::string>& recognised_words, int count)
{
	if (recognised_words.size() != count)
	{
		rd_warn("the number of arguments is incorrect");
		return 0;
	}
	return 1;
}

Utils::ECommands Utils::recognise_command(std::string word)
{
	if (auto search = mapping.find(word); search != mapping.end())
	{
		return search->second;
	}
	return Utils::ECommands::NOT_RECOGNISED;
}

void Utils::recognise_words(std::string client_command, std::list<std::string>& recognised_words)
{
	std::stringstream cc_stream(client_command);
	std::string word;
	while (std::getline(cc_stream, word, ' '))
	{
		recognised_words.push_back(word);
	}
}
