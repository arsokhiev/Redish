#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Redish
{

	class Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return client_logger; }

	private:
		static std::shared_ptr<spdlog::logger> client_logger;
	};

}

#define rd_debug(...)		::Redish::Log::get_client_logger()->trace(__VA_ARGS__);
#define rd_info(...)		::Redish::Log::get_client_logger()->info(__VA_ARGS__);
#define rd_warn(...)		::Redish::Log::get_client_logger()->warn(__VA_ARGS__);
#define rd_error(...)		::Redish::Log::get_client_logger()->error(__VA_ARGS__);
#define rd_critical(...)	::Redish::Log::get_client_logger()->critical(__VA_ARGS__);