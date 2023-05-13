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
