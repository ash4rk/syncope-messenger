#include "Networking/tcp_client.h"
#include "Log/log.h"
#include <boost/asio/async_result.hpp>
#include <boost/system/detail/error_code.hpp>
#include <sstream>
#include <iostream>

namespace Syncopy {
    TCPClient::TCPClient(const std::string &address, int port) : _socket(_ioContext) {
        io::ip::tcp::resolver resolver {_ioContext};
        _endpoints = resolver.resolve(address, std::to_string(port));
    }

    void TCPClient::Run() {
        SYNCOPE_TRACE("Run TCPClient...");
        io::async_connect(_socket, _endpoints, [this](boost::system::error_code ec, io::ip::tcp::endpoint ep) {
            if (!ec) asyncRead();
            else SYNCOPE_ERROR("Run Error {0} {1}", ec.value(), ec.message());
        });

        _ioContext.run();
    }

    void TCPClient::Stop() {
        boost::system::error_code ec;
        _socket.close(ec);
        if (ec) {
          SYNCOPE_ERROR("Stop Error {0} {1}", ec.value(), ec.message());
        }
        SYNCOPE_TRACE("TCPClient was stopped");
    }

    void TCPClient::Post(const std::string &message) {
        SYNCOPE_TRACE("Post message:{0}", message);
        bool queueIdle = _outgoingMessages.empty();
        _outgoingMessages.push(message);

        if (queueIdle) {
          asyncWrite();
        }
    }

    void TCPClient::asyncRead() {
        io::async_read_until(_socket, _streamBuf, "\n", [this](boost::system::error_code ec, size_t bytesTransferred) {
           onRead(ec, bytesTransferred);
        });
    }

    void TCPClient::onRead(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
          SYNCOPE_ERROR("onRead Error {0} {1}", ec.value(), ec.message());
          Stop();
          return;
        }

        std::stringstream message;
        message << std::istream{&_streamBuf}.rdbuf();
        SYNCOPE_TRACE("Get message:{0}", message.str());
        OnMessage(message.str());
        asyncRead();
    }

    void TCPClient::asyncWrite() {
        io::async_write(_socket, io::buffer(_outgoingMessages.front()), [this](boost::system::error_code ec, size_t bytesTransferred) {
            onWrite(ec, bytesTransferred);
        });
    }

    void TCPClient::onWrite(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
          SYNCOPE_ERROR("onWrite Error {0} {1}", ec.value(), ec.message());
          Stop();
          return;
        }
        _outgoingMessages.pop();

        if (!_outgoingMessages.empty()) {
            asyncWrite();
        }
    }
} // namespace Syncopy
