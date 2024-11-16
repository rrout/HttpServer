#ifndef __CONTROLLER_V1_H__
#define __CONTROLLER_V1_H__
#include "Utils.h"
#include "IController.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>

#include "Models.h"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class ControllerV1 : public IController {
public:
        void display() override;
        http::response<http::string_body> handle_request(http::request<http::string_body> const& req) override;

};

#endif

