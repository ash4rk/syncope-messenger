#pragma once

#include "spdlog/spdlog.h"
#include <memory>

namespace Syncopy {

  class Log
  {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return _logger; }

  private:
    static std::shared_ptr<spdlog::logger> _logger;
  };
}

// Log macros

#define SYNCOPE_TRACE(...) ::Syncopy::Log::GetLogger()->trace(__VA_ARGS__)
#define SYNCOPE_INFO(...) ::Syncopy::Log::GetLogger()->info(__VA_ARGS__)
#define SYNCOPE_WARN(...) ::Syncopy::Log::GetLogger()->warn(__VA_ARGS__)
#define SYNCOPE_ERROR(...) ::Syncopy::Log::GetLogger()->error(__VA_ARGS__)
#define SYNCOPE_FATAL(...) ::Syncopy::Log::GetLogger()->fatal(__VA_ARGS__)
