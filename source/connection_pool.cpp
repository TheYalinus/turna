#include "connection_pool.hpp"
#include "curl_wrapper.hpp"
#include "instance_conf.hpp"
#include "share_wrapper.hpp"
#include <curl/curl.h>
#include <memory>
turna::ConnectionPool::ConnectionPool(std::string & url , InstanceConf & instanceConf):shareObject(), instanceConf(instanceConf),curlObjects(){
    shareObject.setShare(CURL_LOCK_DATA_DNS);
    shareObject.setShare(CURL_LOCK_DATA_SSL_SESSION);
    for (int i =0 ; i< this->instanceConf.connection_count; i++ ){
        //curlObjects.push_back(CurlWrapper().setUrl(url).setUsrAgent(instanceConf.user_agent).setDNS(instanceConf.dns).setKeepConnection(true).setShareHandle(shareObject.getSharePtr()).setCurlVerbose());
        curlObjects.push_back(std::make_shared<CurlWrapper>());
        curlObjects.back()->setUrl(url).setUsrAgent(instanceConf.user_agent).setDNS(instanceConf.dns).setKeepConnection(true).setShareHandle(shareObject.getSharePtr()).setCurlVerbose();
    }
}
