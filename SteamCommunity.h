//
// Created by Max on 2. 4. 2021.
//

#ifndef STEAMBOT_STEAMCOMMUNITY_H
#define STEAMBOT_STEAMCOMMUNITY_H
#include <string>
#include <functional>
#include <unordered_map>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <utility>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>

#include <boost/certify/https_verification.hpp>
#include "WebRequest.h"
#include "rapidjson/document.h"

namespace asio = boost::asio;    // from <boost/asio.hpp>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using net = boost::asio::ip::tcp;    // from <boost/asio.hpp>

class SteamCommunity {
	net::resolver resolver_;
	asio::any_io_executor ex;
	ssl::context& ctx;
	beast::flat_buffer buffer_; // (Must persist between reads)
	http::request<http::string_body> req_;
	http::response<http::string_body> res_;
	const std::string host;
	WebRequest* p_apiRequest = nullptr;
	void shutdown();
public:
	SteamCommunity(const asio::any_io_executor& ex, ssl::context& ctx, std::string host);
    void request(std::string endpoint, bool post, const std::unordered_map<std::string, std::string>& data, std::string referer, const std::function<void(http::response <boost::beast::http::string_body >)>& callback);
	void getUserInventory(uint64_t steamid, uint32_t appid, uint32_t contextID, bool tradableOnly, std::string language, std::function<void()> callback);
};


#endif //STEAMBOT_STEAMCOMMUNITY_H
