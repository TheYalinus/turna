#include "share_wrapper.hpp"
#include "exceptions.hpp"
#include <curl/curl.h>
turna::ShareWrapper::ShareWrapper():Share(curl_share_init(), curl_share_cleanup){};
CURLSH * turna::ShareWrapper::getSharePtr(){
    return this->Share.get();
}
void turna::ShareWrapper::setShare(curl_lock_data sharetype){
    auto sh = curl_share_setopt(this->getSharePtr(), CURLSHOPT_SHARE, sharetype);
    if(sh)
        throw turna::CurlShareError(curl_share_strerror(sh));
}
void turna::ShareWrapper::unSetShare(curl_lock_data sharetype){
    auto sh = curl_share_setopt(this->getSharePtr(), CURLSHOPT_UNSHARE, sharetype);
    if(sh)
        throw turna::CurlShareError(curl_share_strerror(sh));
}
