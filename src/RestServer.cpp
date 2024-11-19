#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <regex>

#include "RestServer.h"
#include "RestRouting.h"
#include "Utils.h"
#include "Models.h"
#include "IController.h"
#include "ControllerV1.h"


void Session :: run() {
    do_read();
}

void Session :: do_read() {
    auto self(shared_from_this());
    http::async_read(socket_, buffer_, req_, [this, self](beast::error_code ec, std::size_t) {
        if (!ec) {
            do_write(RestRouting::handle_request(req_));
        }
    });
}

void Session :: do_write(http::response<http::string_body> res) {
    auto self(shared_from_this());
    auto sp = std::make_shared<http::response<http::string_body>>(std::move(res));
    http::async_write(socket_, *sp, [this, self, sp](beast::error_code ec, std::size_t) {
        socket_.shutdown(tcp::socket::shutdown_send, ec);
    });
}


Listener :: Listener(net::io_context& ioc, tcp::endpoint endpoint)
    : ioc_(ioc), acceptor_(net::make_strand(ioc)) {
    beast::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
        std::cerr << "Open error: " << ec.message() << std::endl;
        return;
    }

    // Allow address reuse
    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (ec) {
        std::cerr << "Set option error: " << ec.message() << std::endl;
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if (ec) {
        std::cerr << "Bind error: " << ec.message() << std::endl;
        return;
    }

    // Start listening for connections
    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if (ec) {
        std::cerr << "Listen error: " << ec.message() << std::endl;
        return;
    }

    //do_accept();
}

// Start accepting incoming connections
void Listener :: run() {
    std::cout << "Server Started....." << std::endl;
    do_accept();
}

void Listener :: do_accept() {
    // The new connection gets its own strand
    std::cout << "Waiting for connection....." << std::endl;
    acceptor_.async_accept(
        net::make_strand(ioc_),
        beast::bind_front_handler(
            &Listener::on_accept,
            shared_from_this()));
}

void Listener :: on_accept(beast::error_code ec, tcp::socket socket) {
    if(!ec)
    {
	    std::cout << "Request Recieved" << std::endl;
        std::make_shared<Session>(std::move(socket))->run();
    }

    // Accept another connection
    do_accept();
}
    

void start() {
    auto const address = net::ip::make_address("0.0.0.0");
    unsigned short port = 50080;
    net::io_context ioc{1};
    
    try {
        std::make_shared<Listener>(ioc, tcp::endpoint{address, port})->run();
        ioc.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
