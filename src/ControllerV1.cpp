#include "ControllerV1.h"
#include "Utils.h"

void ControllerV1::display() {

}

http::response<http::string_body> ControllerV1::handle_request(http::request<http::string_body> const& req) {
    std::string response_message;
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());


    std::cout << "Method: " << req.method() << " endpoint : " << req.target() << " Data: " <<  req.body() << std::endl;
    // Respond to GET request with "Hello, World!"
    if (req.method() == http::verb::get) {
        response_message = "Hello, World!";
    } else if (req.method() == http::verb::post && req.target() == "/apiv1/data") {
        // Handle POST request
        auto request = req.body();
        response_message = "Received: " + request;
    } else if (req.method() == http::verb::post && req.target() == "/apiv1/PutVnet") {
        // Handle POST request
        auto request = req.body();
        response_message = "Received: " + request;
        res.set(http::field::content_type, "application/json");
    }else if (req.method() == http::verb::post && req.target() == "/apiv1/PutMapping") {
        // Handle POST request
        auto jsonMap = Utils::parse_json(req.body());

        for (const auto &pair : jsonMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        }
        MappingReq request(jsonMap);
        response_message = request.Process();
        res.set(http::field::content_type, "application/json");
    } else {
        std::cout << "Responding Bad Request" << std::endl;
        response_message = "Bad Request";
    }

    if (!response_message.empty()) {
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.keep_alive(req.keep_alive());
        res.body() = response_message;
        res.prepare_payload();
        return res;
    } else {
        response_message = "Processing failed";
        return res;
    }

    // Default response for unsupported methods
    return http::response<http::string_body>{http::status::bad_request, req.version()};
}
