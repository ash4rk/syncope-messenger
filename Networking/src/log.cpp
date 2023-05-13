#include "Log/log.h"
#include <memory>
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Syncopy {

  std::shared_ptr<spdlog::logger> Log::_logger;

  void Log::Init()
  {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    _logger = spdlog::stdout_color_mt("Syncopy");
    _logger->set_level(spdlog::level::trace);
  }


}
