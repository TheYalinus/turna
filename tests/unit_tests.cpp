#include "curl_wrapper.hpp"
#include "utils.hpp"
#include <catch2/catch_test_macros.hpp>
#include <istream>
#include <nlohmann/json_fwd.hpp>
#include <sstream>
#include <string>
#include <turna.hpp>
#include <iostream>

TEST_CASE("A basic file download operation should be correctly performed via using CurlWrapper class"){
    turna::CurlWrapper wrapper;
    SECTION("A non ranged request"){
        wrapper.setUrl("https://httpbin.org/anything");
        auto [curlcode,http_return] =wrapper.executeCurl();
        REQUIRE(curlcode == 0);
        REQUIRE(http_return == 200);
    }
    SECTION("A non ranged request with an user agent and output redirecting"){
        wrapper.setUrl("https://httpbin.org/anything");
        auto user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/152.0.0.0 Safari/537.36";
        wrapper.setUsrAgent(user_agent);
        std::stringstream strm;
        wrapper.setWriteFunction(turna::writeFunctionStream);
        wrapper.setWritePointer(&strm);
        wrapper.executeCurl();
        auto json = nlohmann::json::parse(strm);
        std::string user_agent_header=  json.at("headers").at("User-Agent");
        REQUIRE(user_agent_header == user_agent );
    }
}
