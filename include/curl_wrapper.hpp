#ifndef CURL_WRAPPER_HPP
#define CURL_WRAPPER_HPP
#include "curl/curl.h"
#include "range_type.hpp"
#include <curl/easy.h>
#include <memory>
#include <string_view>
namespace turna {
    class CurlWrapper{
        public:
            CurlWrapper(bool keep_connection=true , bool curl_verbose= false);
            void setUrl(std::string_view url);
            void setHeaderOnly(bool option= true);
            void setFollowRedirects(bool option= true);
            void setKeepConnection(bool option);
            void setCurlVerbose(bool option=true);
            void setRange(RangeType range);
        private:
            std::unique_ptr<CURL , decltype(&curl_easy_cleanup)> Curl;
    };
}
#endif
