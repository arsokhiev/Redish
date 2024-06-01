#include "ServerLog.h"

namespace Redish
{

	std::shared_ptr<spdlog::logger> Log::server_logger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		server_logger = spdlog::stdout_color_mt("Server_Log");
		server_logger->set_level(spdlog::level::trace);
	}

}