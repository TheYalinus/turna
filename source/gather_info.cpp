#include "gather_info.hpp"
#include "download_conf.hpp"
#include "exceptions.hpp"
#include <chrono>
#include <thread>
turna::DownloadConfComplex turna::gatherData(turna::CurlWrapper & Curl, std::string & url , unsigned int partCount){
    try {
    return _gatherHeadMethod(Curl, url, partCount);
    } catch (HeaderRejectedError) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return _gatherGetMethod(Curl, url, partCount);
    }
}
turna::DownloadConfComplex turna::_gatherHeadMethod(turna::CurlWrapper & Curl, std::string & url,  unsigned int partCount){
    Curl.setHeaderOnly();
    Curl.setUrl(url);
    if (auto [cc , httpcode]= Curl.executeCurl(); cc != CURLE_OK || httpcode != 200 ) {
        throw HeaderRejectedError("Server rejected header response");
    }
    auto effectiveUrl = Curl.getEffectiveUrl();
    auto filename=  effectiveUrl.substr(effectiveUrl.find_last_of("/")+1,(effectiveUrl.find('?')-(effectiveUrl.find_last_of("/")))-1);
    auto fileext= effectiveUrl.substr(effectiveUrl.find_last_of(".")+1);
    return {partCount ,url, Curl.getHeader("Content-Type").value , filename , fileext , Curl.getTotalSize() };
}
turna::DownloadConfComplex turna::_gatherGetMethod(turna::CurlWrapper & Curl, std::string & url ,unsigned int partCount){
    Curl.setHeaderOnly(false);
    Curl.setUrl(url);
    Curl.setWriteFunction(turna::_dummyWriteCallback);
    Curl.executeCurl();
    if(Curl.getTotalSize() ==0)
        throw GetRejectedError("Server didnt gave filesize");
    auto effectiveUrl = Curl.getEffectiveUrl();
    auto filename=  effectiveUrl.substr(effectiveUrl.find_last_of("/")+1,(effectiveUrl.find('?')-(effectiveUrl.find_last_of("/")))-1);
    auto fileext= effectiveUrl.substr(effectiveUrl.find_last_of(".")+1);
    return {partCount , url, Curl.getHeader("Content-Type").value , filename , fileext , Curl.getTotalSize() };
}
size_t turna::_dummyWriteCallback(char *data, size_t size, size_t nmemb, void *clientp){
    return -1;
}
