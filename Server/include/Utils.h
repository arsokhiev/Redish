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
#include <map>
#include <unordered_map>
#include <WinSock2.h>

#include "ServerLog.h"

class Utils
{
public:
	enum class ECommands
	{
		PUT,
		GET,
		DEL,
		COUNT,
		NOT_RECOGNISED
	};

	static const std::map<std::string, ECommands> mapping;

	static Utils::ECommands recognise_command(std::string word);

	static void recognise_words(std::string client_command,
		std::list<std::string>& recognised_words);

	static bool check_command_argc(std::list<std::string>& recognised_words, int count);
};