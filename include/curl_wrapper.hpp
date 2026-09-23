#ifndef CURL_WRAPPER_HPP
#define CURL_WRAPPER_HPP
#include "curl/curl.h"
#include "range_type.hpp"
#include <curl/easy.h>
#include <curl/header.h>
#include <curl/system.h>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
namespace turna {
    class CurlWrapper{
        using curlReturnType = std::pair <CURLcode,long>;
        public:
            CurlWrapper(bool keep_connection=true , bool curl_verbose= false);
            void setUrl(std::string_view url);
            void setHeaderOnly(bool option= true);
            void setFollowRedirects(bool option= true);
            void setKeepConnection(bool option);
            void setCurlVerbose(bool option=true);
            void setRange(RangeType range);
            void setDNS(std::vector<std::string> dnslist);
            void setDNS(std::string_view dns);
            void setProxy(std::string_view proxy);
            void setProxyUsername(std::string_view username);
            void setProxyPassword(std::string_view proxy);
            void disableProxy();
            void setProgress(bool option=true);
            void setShareHandle(CURLSH * share_handle);
            void setUsrAgent(std::string_view user_agent);
            void resetAttributes();
            CURL * getRawCurl();
            std::string getEffectiveUrl();
            long getTotalSize();
            struct curl_header getHeader(std::string_view value);
            curlReturnType executeCurl();

        private:
            std::unique_ptr<CURL , decltype(&curl_easy_cleanup)> Curl;
    };
}
#endif
