#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace soul {
	class SOUL_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


// core log macros so that they can be used like this: SL_CORE_ERROR("This is an error message with a number: {}", 42); instead of ::soul::Log::GetCoreLogger()->error("This is an error message with a number: {}", 42);

#define SL_CORE_TRACE(...)		::soul::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SL_CORE_INFO(...)		::soul::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SL_CORE_WARN(...)		::soul::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SL_CORE_ERROR(...)		::soul::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SL_CORE_CRITICAL(...)	::soul::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define SL_CLIENT_FATAL(...)		::soul::Log::GetClientLogger()->fatal(__VA_ARGS__)

// client log macros so that they can be used like this: SL_ERROR("This is an error message with a number: {}", 42); instead of ::soul::Log::GetClientLogger()->error("This is an error message with a number: {}", 42);

#define SL_TRACE(...)		::soul::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SL_INFO(...)		::soul::Log::GetClientLogger()->info(__VA_ARGS__)
#define SL_WARN(...)		::soul::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SL_ERROR(...)		::soul::Log::GetClientLogger()->error(__VA_ARGS__)
#define SL_CRITICAL(...)	::soul::Log::GetClientLogger()->critical(__VA_ARGS__)
#define SL_FATAL(...)		::soul::Log::GetClientLogger()->fatal(__VA_ARGS__)