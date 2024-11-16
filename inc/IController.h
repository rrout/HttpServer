#ifndef __ICONTROLLER_H__
#define __ICONTROLLER_H__
#include "Utils.h"


class IController {
public:
    virtual void display() = 0;
    virtual http::response<http::string_body> handle_request(http::request<http::string_body> const& req)  = 0;
    virtual ~IController() = default;
};


#endif
