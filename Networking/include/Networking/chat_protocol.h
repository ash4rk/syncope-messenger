#pragma once

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <memory>
#include <queue>
#include <string>

namespace Syncopy {

enum Command { AUTH, SAY, BAD_PATH };

struct AuthMessage {
  std::string login;
  std::string password;
};

struct SayMessage {
  std::string body;
};

  const std::string SendAuth(const std::string& login, const std::string& password);
  std::string SendSay(std::string body);
  Command GetCommandName(std::string message);
  AuthMessage ParseAuth(std::string message);
  SayMessage ParseSay(std::string message);

  Command _hashit(std::string const &inString);

} // namespace Syncopy
