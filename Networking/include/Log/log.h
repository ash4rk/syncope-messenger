#pragma once

#include "spdlog/spdlog.h"
#include <memory>

namespace Syncope {

class Log {
public:
  static void Init();
  inline static std::shared_ptr<spdlog::logger> &GetLogger() { return _logger; }

private:
  static std::shared_ptr<spdlog::logger> _logger;
};
} // namespace Syncope

// Log macros
#define SYNCOPE_TRACE(...)  ::Syncope::Log::GetLogger()->trace(__VA_ARGS__)
#define SYNCOPE_INFO(...)   ::Syncope::Log::GetLogger()->info(__VA_ARGS__)
#define SYNCOPE_WARN(...)   ::Syncope::Log::GetLogger()->warn(__VA_ARGS__)
#define SYNCOPE_ERROR(...)  ::Syncope::Log::GetLogger()->error(__VA_ARGS__)
#define SYNCOPE_FATAL(...)  ::Syncope::Log::GetLogger()->fatal(__VA_ARGS__)
