#include "ControllerV1.h"
#include "Utils.h"
#include "Models.h"

void ControllerV1::display() {

}

http::response<http::string_body> ControllerV1::handle_request(http::request<http::string_body> const& req) {
    std::string response_message;
    http::response<http::string_body> res{http::status::ok, req.version()};
    res.set(http::field::server, "Beast");
    res.set(http::field::content_type, "text/plain");
    res.keep_alive(req.keep_alive());


    std::cout << "Method: " << req.method() << " endpoint : " << req.target() << " Data: " <<  req.body() << std::endl;
    if (req.method() == http::verb::get && (req.target() == "" || req.target() == "/apiv1/" ||  req.target() == "/apiv1/help")) {
        response_message += "Endpoints are:\n";
        response_message += "POST : /apiv1/PutVnet \n";
        response_message += "POST : /apiv1/GetVnet \n";
        response_message += "POST : /apiv1/PutMapping \n";
        response_message += "GET  : /apiv1/GetMapping \n";
        response_message += "GET  : /apiv1/GetConfig \n";
        response_message += "GET  : /apiv1/PutConfig \n";
        response_message += "GET  : /apiv1/help \n";
    } else if (req.method() == http::verb::get && boost::algorithm::starts_with(req.target().to_string(), "/apiv1/GetVnet")) {
        if (req.target() == "/apiv1/GetVnet") {
            response_message = "Received : " + req.target().to_string();
        } else {
            auto target = req.target().to_string();
            size_t question_pos = target.find('?');
            if (question_pos != std::string::npos) {
                std::string query_string = target.substr(question_pos + 1);
                auto query_map = Utils::parse_query(query_string);
                VentReq request(query_map);
                response_message = request.Dump();
            } else {
                response_message = "Bad GET Received : " + req.target().to_string();
            }
        }
    } else if (req.method() == http::verb::post && req.target() == "/apiv1/PutVnet") {
        auto jsonMap = Utils::parse_json(req.body());
        VentReq request(jsonMap);
        response_message = request.Process();
        res.set(http::field::content_type, "application/json");
    } else if (req.method() == http::verb::get &&  boost::algorithm::starts_with(req.target().to_string(), "/apiv1/GetMapping")) {
        if (req.target() == "/apiv1/GetMapping") {
            response_message = "Received : " + req.target().to_string();
        } else {
            auto target = req.target().to_string();
            size_t question_pos = target.find('?');
            if (question_pos != std::string::npos) {
                std::string query_string = target.substr(question_pos + 1);
                auto query_map = Utils::parse_query(query_string);
                MappingReq request(query_map);
                response_message = request.Dump();
            } else {
                response_message = "Bad GET Received : " + req.target().to_string();
            }

        }
    } else if (req.method() == http::verb::post && req.target() == "/apiv1/PutMapping") {
        auto jsonMap = Utils::parse_json(req.body());
        MappingReq request(jsonMap);
        response_message = request.Process();
        res.set(http::field::content_type, "application/json");
    } else if (req.method() == http::verb::post && req.target() == "/apiv1/GetConfig") {
        auto jsonMap = Utils::parse_json(req.body());
        MappingReq request(jsonMap);
        response_message = request.Process();
        res.set(http::field::content_type, "application/json");
    } else if (req.method() == http::verb::post && req.target() == "/apiv1/PutConfig") {
        auto jsonMap = Utils::parse_json(req.body());
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
