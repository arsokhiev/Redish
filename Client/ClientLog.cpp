#include "ClientLog.h"

namespace Redish
{

	std::shared_ptr<spdlog::logger> Log::client_logger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		client_logger = spdlog::stdout_color_mt("Client_Log");
		client_logger->set_level(spdlog::level::trace);
	}

}