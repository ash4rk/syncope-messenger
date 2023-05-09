#pragma once

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <memory>
#include <queue>
#include <string>

namespace Syncopy {

struct AuthMessage {
  std::string login;
  std::string password;
};

struct SayMessage {
  std::string body;
};

  std::string SendAuth(std::string login, std::string password);
  std::string SendSay(std::string body);
  std::string GetCommandName(std::string message);
  AuthMessage ParseAuth(std::string message);
  SayMessage ParseSay(std::string message);

} // namespace Syncopy
