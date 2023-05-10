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
  const std::string SendSay(std::string body);
  const Command GetCommandName(const std::string message);
  const AuthMessage ParseAuth(const std::string message);
  const SayMessage ParseSay(const std::string message);

  Command _hashit(std::string const &inString);

} // namespace Syncopy
