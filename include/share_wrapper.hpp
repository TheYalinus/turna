#ifndef SHARE_WRAPPER_HPP
#define SHARE_WRAPPER_HPP
#include <curl/curl.h>
#include <memory>
namespace turna {
    class ShareWrapper{
        public:
            ShareWrapper();
            void setShare(curl_lock_data sharetype);
            void unSetShare(curl_lock_data sharetype);
            CURLSH * getSharePtr();
        private:
            std::unique_ptr<CURLSH , decltype(&curl_share_cleanup)> Share;
    };
}
#endif
