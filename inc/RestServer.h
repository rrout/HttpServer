#ifndef __REST__SERVER_H__
#define __REST__SERVER_H__
#include "Utils.h"

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(tcp::socket socket) : socket_(std::move(socket)) {}
    void run();
private:
    void do_read();
    void do_write(http::response<http::string_body> res);
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
};




class Listener : public std::enable_shared_from_this<Listener> {
public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint);
    void run();
    
private:
    void do_accept();
    void on_accept(beast::error_code ec, tcp::socket socket);
    
    net::io_context& ioc_;
    tcp::acceptor acceptor_;
};
#endif
