#include "Networking/tcp_client.h"
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
        io::async_connect(_socket, _endpoints, [this](boost::system::error_code ec, io::ip::tcp::endpoint ep) {
            if (!ec) asyncRead();
            else std::cout << "Run Error " << ec << "! " << ec.message() << std::endl;
        });

        _ioContext.run();
    }

    void TCPClient::Stop() {
        boost::system::error_code ec;
        _socket.close(ec);
        if (ec) {
          std::cout << "Stop Error " << ec << "! " << ec.message() << std::endl;
        }
    }

    void TCPClient::Post(const std::string &message) {
      std::cout << "Post func call. message is: "<< message << " type is " << typeid(message).name()  << std::endl;
        bool queueIdle = _outgoingMessages.empty();
        _outgoingMessages.push(message);

        if (queueIdle) {
          std::cout << "!queueIdle" << std::endl;
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
            std::cout << "onRead Error " << ec << "! " << ec.message() << std::endl;
            Stop();
            return;
        }

        std::stringstream message;
        message << std::istream{&_streamBuf}.rdbuf();
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
            std::cout << "onWrite Error " << ec << "! " << ec.message() << std::endl;
            Stop();
            return;
        }
        std::cout << "onWrite without errors. popping message: " << _outgoingMessages.front()  << std::endl;
        std::cout << "bytesTransferred: "<< bytesTransferred << std::endl;
        _outgoingMessages.pop();

        if (!_outgoingMessages.empty()) {
            std::cout << " _outgoingMessage not empty! " << std::endl;
            asyncWrite();
        }
    }
} // namespace Syncopy
