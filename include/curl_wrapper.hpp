#ifndef CURL_WRAPPER_HPP
#define CURL_WRAPPER_HPP
#include "curl/curl.h"
#include "range_type.hpp"
#include <curl/easy.h>
#include <curl/header.h>
#include <curl/system.h>
#include <memory>
#include <string>

#include <vector>
namespace turna {
    class CurlWrapper{
        using curlReturnType = std::pair <CURLcode,long>;
        public:
            CurlWrapper(bool keep_connection=true , bool curl_verbose= false);
            void setUrl(const std::string& url);
            void setHeaderOnly(bool option= true);
            void setFollowRedirects(bool option= true);
            void setKeepConnection(bool option);
            void setCurlVerbose(bool option=true);
            void setRange(const RangeType& range);
            void setDNS(const std::vector<std::string>& dnslist);
            void setDNS(const std::string& dns);
            void setProxy(const std::string& proxy);
            void setProxyUsername(const std::string& username);
            void setProxyPassword(const std::string& proxy);
            void disableProxy();
            void setProgress(bool option=true);
            void setShareHandle(CURLSH * share_handle);
            void setUsrAgent(const std::string& user_agent);
            void resetAttributes();
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
