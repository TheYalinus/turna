#include "curl_wrapper.hpp"
#include "range_type.hpp"
#include "exceptions.hpp"
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/header.h>
#include <curl/system.h>
#include <filesystem>
#include <string>
#include <string_view>
turna::CurlWrapper::CurlWrapper(bool keep_connection, bool curl_verbose):Curl(curl_easy_init(), curl_easy_cleanup){
    if(keep_connection)
        this->setKeepConnection(true);
    if(curl_verbose)
        this->setCurlVerbose();
}
void turna::CurlWrapper::setFollowRedirects(bool option){
    if(option)
        curl_easy_setopt(this->Curl.get(),CURLOPT_FOLLOWLOCATION,1L);
    else
        curl_easy_setopt(this->Curl.get(),CURLOPT_FOLLOWLOCATION,0L);
}
turna::curlReturnType turna::CurlWrapper::executeCurl(){
    curlReturnType result;
    result.first = curl_easy_perform(this->getRawCurl());
    curl_easy_getinfo(this->getRawCurl(), CURLINFO_RESPONSE_CODE, &result.second);
    return result;
}
void turna::CurlWrapper::setUrl(const std::string& url){
    curl_easy_setopt(this->Curl.get(),CURLOPT_URL,url.c_str());
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
void turna::CurlWrapper::setRange(const turna::RangeType& range){
    curl_easy_setopt(this->Curl.get(), CURLOPT_RANGE, range.getCurlRange().c_str());
}
void turna::CurlWrapper::setUsrAgent(const std::string& user_agent){
    curl_easy_setopt(this->Curl.get(), CURLOPT_USERAGENT, user_agent.c_str());
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
void turna::CurlWrapper::setProxy(const std::string& proxy){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_PROXY, proxy.c_str());
}
void turna::CurlWrapper::setProxyPassword(const std::string& password){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_PROXYPASSWORD, password.c_str());
}
void turna::CurlWrapper::setProxyUsername(const std::string& username){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_PROXYUSERNAME, username.c_str());
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
std::string turna::CurlWrapper::getEffectiveUrl(){
    char * effective_url_buff_c;
    curl_easy_getinfo(this->getRawCurl(), CURLINFO_EFFECTIVE_URL, &effective_url_buff_c);
    if(effective_url_buff_c != NULL){
        return std::string{effective_url_buff_c};
    }
    else {
        throw CurlGetInfoError("Cannot get effective url");
    }
}
struct curl_header turna::CurlWrapper::getHeader(const std::string& value){
    struct curl_header *data;
    curl_easy_header(this->getRawCurl(), value.c_str(), 0, CURLH_HEADER, -1, &data);
    return *data;
}
void turna::CurlWrapper::setWriteFunction(size_t(*func)(char* ,size_t, size_t ,void *)){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_WRITEFUNCTION, func);
}
void turna::CurlWrapper::setWritePointer(void * pointer){
    curl_easy_setopt(this->getRawCurl(), CURLOPT_WRITEDATA, pointer);
}
