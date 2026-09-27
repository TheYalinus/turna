#ifndef CURL_WRAPPER_HPP
#define CURL_WRAPPER_HPP
#include "curl/curl.h"
#include "range_type.hpp"
#include <cstddef>
#include <curl/easy.h>
#include <curl/header.h>
#include <curl/system.h>
#include <functional>
#include <memory>
#include <filesystem>
#include <string>

#include <vector>
namespace turna {
    using curlReturnType = std::pair <CURLcode,long>;
    class CurlWrapper{
        public:
            CurlWrapper(bool keep_connection=true , bool curl_verbose= false);
            CurlWrapper& setUrl(const std::string& url);
            CurlWrapper& setHeaderOnly(bool option= true);
            CurlWrapper& setFollowRedirects(bool option= true);
            CurlWrapper& setKeepConnection(bool option);
            CurlWrapper& setCurlVerbose(bool option=true);
            CurlWrapper& setRange(const RangeType& range);
            CurlWrapper& setDNS(const std::vector<std::string>& dnslist);
            CurlWrapper& setDNS(const std::string& dns);
            CurlWrapper& setProxy(const std::string& proxy);
            CurlWrapper& setProxyUsername(const std::string& username);
            CurlWrapper& setProxyPassword(const std::string& proxy);
            CurlWrapper& setWriteFunction(size_t(func)(char* ,size_t, size_t ,void *));
            CurlWrapper& setWritePointer(void *);
            CurlWrapper& disableProxy();
            CurlWrapper& setProgress(bool option=true);
            CurlWrapper& setShareHandle(CURLSH * share_handle);
            CurlWrapper& setUsrAgent(const std::string& user_agent);
            CurlWrapper& resetAttributes();
            CURL * getRawCurl();
            std::string getEffectiveUrl();
            long getTotalSize();
            struct curl_header getHeader(const std::string& value);
            curlReturnType executeCurl();

        private:
            std::unique_ptr<CURL , decltype(&curl_easy_cleanup)> Curl;
    };
}
#endif
