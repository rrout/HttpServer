#ifndef __UTILS_H__
#define __UTILS_H__
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <regex>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/algorithm/string.hpp>


namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


class Utils {
public:
    static std::string trim(const std::string &s) {
        size_t start = s.find_first_not_of(" \t\n\r");
        size_t end = s.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
    }

    static std::map<std::string, std::string> parse_json(const std::string &jsonString) {
        std::map<std::string, std::string> jsonMap;
        size_t pos = 0;

        while ((pos = jsonString.find('"', pos)) != std::string::npos) {
            size_t end = jsonString.find('"', pos + 1);
            if (end == std::string::npos) break;

            std::string key = jsonString.substr(pos + 1, end - pos - 1);
            pos = jsonString.find(':', end);
            if (pos == std::string::npos) break;

            pos = jsonString.find_first_not_of(" \t\n\r", pos + 1);
            if (pos == std::string::npos) break;

            char valueDelimiter = (jsonString[pos] == '"') ? '"' : ',';
            size_t valueStart = (jsonString[pos] == '"') ? pos + 1 : pos;
            size_t valueEnd = (jsonString[pos] == '"') ? jsonString.find('"', valueStart) : jsonString.find(',', valueStart);

            if (valueEnd == std::string::npos) {
                valueEnd = jsonString.size();
            }

            std::string value = jsonString.substr(valueStart, valueEnd - valueStart);
            if (valueDelimiter == '"') {
                pos = valueEnd + 1; // Skip the closing quote
            } else {
                pos = valueEnd;
            }

            jsonMap[key] = trim(value);

            pos = jsonString.find(',', pos) + 1;
            if (pos == 0) break;
        }

        return jsonMap;
    }

    static bool isValidGUID(const std::string& guid) {
        const std::regex guidRegex("^[{]?[0-9a-fA-F]{8}[-]?[0-9a-fA-F]{4}[-]?[0-9a-fA-F]{4}[-]?[0-9a-fA-F]{4}[-]?[0-9a-fA-F]{12}[}]?$");
        return std::regex_match(guid, guidRegex);
    }


    // Function to parse query string
    static std::map<std::string, std::string> parse_query(const std::string& query) {
        std::map<std::string, std::string> query_map;
        std::vector<std::string> pairs;
        boost::split(pairs, query, boost::is_any_of("&"));
        for (const auto& pair : pairs) {
            size_t pos = pair.find("=");
            if (pos != std::string::npos) {
                std::string key = pair.substr(0, pos);
                std::string value = pair.substr(pos + 1);
                query_map[key] = value;
            }
        }
        return query_map;
    }
};



#endif

