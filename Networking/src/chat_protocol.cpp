#include "Networking/chat_protocol.h"

#include "boost/beast/core/detail/base64.hpp"
#include <iostream>
#include <string>

namespace Syncopy {

const std::string SendAuth(const std::string &login,
                           const std::string &password) {
  return "AUTH " + login + ":" + password + "\n";
}

const std::string SendSay(std::string body) {
  // Encode string to base64
  std::string base64EncodedBody;
  base64EncodedBody.resize(
      boost::beast::detail::base64::encoded_size(body.size()));
  boost::beast::detail::base64::encode(&base64EncodedBody[0], body.c_str(),
                                       body.size());
  return "SAY " + base64EncodedBody + "\n";
}

const std::string SendShout(const std::string& username, std::string body) {
  // Encode string to base64
  std::string base64EncodedBody;
  base64EncodedBody.resize(
      boost::beast::detail::base64::encoded_size(body.size()));
  boost::beast::detail::base64::encode(&base64EncodedBody[0], body.c_str(),
                                       body.size());
  return "SHOUT " + username + ": " + base64EncodedBody + "\n";
}

const Command GetCommandName(const std::string message) {
  std::istringstream iss(message);
  std::string command;
  getline(iss, command, ' ');
  std::cout << "Command is: " << command << std::endl;
  return _hashit(command);
}

const AuthMessage ParseAuth(const std::string message) {
  AuthMessage credentials;
  std::istringstream iss(message);
  std::string command;
  std::string login;
  std::string password;
  getline(iss, command, ' ');
  getline(iss, login, ':');
  getline(iss, password, '\n');
  std::cout << "Login is: " << login << std::endl;
  std::cout << "Password is: " << password << std::endl;
  credentials.login = login;
  credentials.password = password;
  return credentials;
}

const SayMessage ParseSay(const std::string message) {
  std::istringstream iss(message);
  std::string command;
  std::string encodedBody;
  getline(iss, command, ' ');
  getline(iss, encodedBody, ' ');
  // Decode the base64-encoded string
  std::string decodedString;
  decodedString.resize(
      boost::beast::detail::base64::decoded_size(encodedBody.size()));
  auto decoded_size = boost::beast::detail::base64::decode(
      &decodedString[0], encodedBody.c_str(), encodedBody.size());
  SayMessage sayMessage;
  sayMessage.body = decodedString;
  return sayMessage;
}

Command _hashit(const std::string &inString) {
  if (inString == "AUTH")
    return AUTH;
  if (inString == "SAY")
    return SAY;
  return BAD_PATH;
}
} // namespace Syncopy
