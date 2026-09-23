#include "curl_wrapper.hpp"
#include "range_type.hpp"
#include <curl/curl.h>
#include <curl/system.h>
#include <string>
#include <string_view>
void turna::CurlWrapper::setUrl(std::string_view url){
    curl_easy_setopt(this->Curl.get(),CURLOPT_URL,url);
}
void turna::CurlWrapper::setHeaderOnly(bool option){
    if(option)
        curl_easy_setopt(this->Curl.get(), CURLOPT_NOBODY, 1L);
    else
        curl_easy_setopt(this->Curl.get(), CURLOPT_NOBODY, 0L);
}
void turna::CurlWrapper::setCurlVerbose(bool option){
    if(option)
        curl_easy_setopt(this->Curl.get(), CURLOPT_VERBOSE, 1L);
    else
        curl_easy_setopt(this->Curl.get(), CURLOPT_VERBOSE, 0L);
}
void turna::CurlWrapper::setRange(turna::RangeType range){
    curl_easy_setopt(this->Curl.get(), CURLOPT_RANGE, range.getCurlRange().c_str());
}
void turna::CurlWrapper::setUsrAgent(std::string_view user_agent){
    curl_easy_setopt(this->Curl.get(), CURLOPT_USERAGENT, user_agent);
}
void turna::CurlWrapper::setShareHandle(CURLSH * share_handle){
    curl_easy_setopt(this->Curl.get(), CURLOPT_SHARE, share_handle);
}
void turna::CurlWrapper::setKeepConnection(bool option){
    if(option)
        curl_easy_setopt(this->Curl.get(), CURLOPT_TCP_KEEPALIVE, 1L);
    else
        curl_easy_setopt(this->Curl.get(), CURLOPT_TCP_KEEPALIVE, 0L);
}
void turna::CurlWrapper::setProgress(bool option){
    if(option)
        curl_easy_setopt(this->getRawCurl(), CURLOPT_NOPROGRESS, 0L);
    else
        curl_easy_setopt(this->getRawCurl(), CURLOPT_NOPROGRESS, 1L);
}
void turna::CurlWrapper::setProxy(std::string_view proxy){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_PROXY, proxy);
}
void turna::CurlWrapper::setProxyPassword(std::string_view password){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_PROXYPASSWORD, password);
}
void turna::CurlWrapper::setProxyUsername(std::string_view username){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_PROXYUSERNAME, username);
}
void turna::CurlWrapper::disableProxy(){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_PROXY, "");
}
CURL * turna::CurlWrapper::getRawCurl(){
    return this->Curl.get();
}
long turna::CurlWrapper::getTotalSize(){
    curl_off_t total_size_buffer = 0;
    curl_easy_getinfo(this->getRawCurl(), CURLINFO_CONTENT_LENGTH_DOWNLOAD_T,&total_size_buffer);
    return total_size_buffer;
}
