#include "Networking/chat_protocol.h"

#include "boost/beast/core/detail/base64.hpp"

namespace Syncopy {

std::string SendAuth(std::string login, std::string password) { return ""; }
std::string SendSay(std::string body) {
  std::string base64EncodedBody;
  base64EncodedBody.resize(boost::beast::detail::base64::encoded_size(body.size()));
  boost::beast::detail::base64::encode(&base64EncodedBody[0], body.c_str(), body.size());
  return "SEND " + base64EncodedBody + "\n";
}
std::string GetCommandName(std::string message) { return ""; }
AuthMessage ParseAuth(std::string message) { return AuthMessage(); }
SayMessage ParseSay(std::string message) { return SayMessage(); }

} // namespace Syncopy
