#include "RestRouting.h"

http::response<http::string_body> RestRouting::handle_request(http::request<http::string_body> const& req) {
    std::string apiV1 = "/apiv1/";
    std::string apiV2 = "/apiv2/";
    std::string response_message;

    // Check API version
    std::string target = req.target().to_string();
    bool is_apiv1 = target.find("/apiv1/") == 0;
    bool is_apiv2 = target.find("/apiv2/") == 0;

    if (!is_apiv1 && !is_apiv2) {
        response_message = "Invalid API version! \n";
        response_message += "Either /apiv1/  OR  /apiv2/ supported. Chose one..... \n";
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
        response_message = " Unsupported HTTP method!";
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
    res.body() += "\n";
    
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());
    res.prepare_payload();
    return res;
}