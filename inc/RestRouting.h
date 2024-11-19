#ifndef __REST__ROUTING__
#define __REST__ROUTING__
#include "Utils.h"
#include "RestServer.h"
#include "RestRouting.h"
#include "Utils.h"
#include "Models.h"
#include "IController.h"
#include "ControllerV1.h"

class RestRouting {
public:
    static http::response<http::string_body> handle_request(http::request<http::string_body> const& req);

};

#endif