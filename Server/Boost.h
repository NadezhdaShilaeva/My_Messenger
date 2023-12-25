#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;