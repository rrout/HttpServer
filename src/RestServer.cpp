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

#include "Utils.h"
#include "Models.h"
#include "IController.h"
#include "ControllerV1.h"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>



http::response<http::string_body> handle_request(http::request<http::string_body> const& req) {
    std::string response_message;

    // Check API version
    std::string target = req.target().to_string();
    bool is_apiv1 = target.find("/apiv1/") == 0;
    bool is_apiv2 = target.find("/apiv2/") == 0;

    if (!is_apiv1 && !is_apiv2) {
        response_message = "Invalid API version!";
        http::response<http::string_body> res{http::status::bad_request, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = response_message;
        res.prepare_payload();
        return res;
    }

    // Check HTTP method and handle accordingly
    if (req.method() == http::verb::get) {
        response_message = "GET request received";
    } else if (req.method() == http::verb::post) {
        response_message = "POST request received";
    } else if (req.method() == http::verb::put) {
        response_message = "PUT request received";
    } else if (req.method() == http::verb::delete_) {
        response_message = "DELETE request received";
    } else {
        response_message = "Unsupported HTTP method!";
        http::response<http::string_body> res{http::status::method_not_allowed, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = response_message;
        res.prepare_payload();
        return res;
    }
    
    http::response<http::string_body> res{http::status::ok, req.version()};
    if (is_apiv1) {
        std::unique_ptr<IController> controller = std::make_unique<ControllerV1>();
        res = controller->handle_request(req);
    } else if (is_apiv2) {
        std::unique_ptr<IController> controller = std::make_unique<ControllerV1>();
        res = controller->handle_request(req);
    }

    
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());
    res.prepare_payload();
    return res;
}



// This class handles an HTTP server connection.
class Session : public std::enable_shared_from_this<Session> {
    tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;

public:
    explicit Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void run() {
        do_read();
    }

private:
    void do_read() {
        auto self(shared_from_this());
        http::async_read(socket_, buffer_, req_, [this, self](beast::error_code ec, std::size_t) {
            if (!ec) {
                do_write(handle_request(req_));
            }
        });
    }

    void do_write(http::response<http::string_body> res) {
        auto self(shared_from_this());
        auto sp = std::make_shared<http::response<http::string_body>>(std::move(res));
        http::async_write(socket_, *sp, [this, self, sp](beast::error_code ec, std::size_t) {
            socket_.shutdown(tcp::socket::shutdown_send, ec);
        });
    }
};

// This class accepts incoming connections and launches the sessions.
class Listener : public std::enable_shared_from_this<Listener> {
    net::io_context& ioc_;
    tcp::acceptor acceptor_;

public:
    Listener(net::io_context& ioc, tcp::endpoint endpoint)
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
    void
    run()
    {
        do_accept();
    }

private:
    void
    do_accept()
    {
        // The new connection gets its own strand
        acceptor_.async_accept(
            net::make_strand(ioc_),
            beast::bind_front_handler(
                &Listener::on_accept,
                shared_from_this()));
    }

    void
    on_accept(beast::error_code ec, tcp::socket socket)
    {
        if(!ec)
        {
		std::cout << "Request Recieved" << std::endl;
                std::make_shared<Session>(std::move(socket))->run();
        }

        // Accept another connection
        do_accept();
    }
    void do_accepat1() {
        acceptor_.async_accept(net::make_strand(ioc_), [this](beast::error_code ec, tcp::socket socket) {
            if (!ec) {
	    	std::cout << "Something wrong" << std::endl;
                std::make_shared<Session>(std::move(socket))->run();
            }
            do_accept();
        });
    }
};

/*
void start1() {
    auto const address = net::ip::make_address("0.0.0.0");
    unsigned short port = 8080;
+     try {
+
+         net::io_context ioc{1};
+
+         std::make_shared<Listener>(ioc, tcp::endpoint{address, port})->run();
    +     std::cout << "Running" <<std::endl;
+         ioc.run();
+     } catch (const std::exception& e) {
+         std::cerr << "Error: " << e.what() << std::endl;
+     }
+ }
*/
void start() {
    auto const address = net::ip::make_address("0.0.0.0");
    unsigned short port = 8080;
    net::io_context ioc{1};
    std::make_shared<Listener>(ioc, tcp::endpoint{address, port})->run();
    ioc.run();
}
