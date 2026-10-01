#include "connection_pool.hpp"
#include "curl_wrapper.hpp"
#include "instance_conf.hpp"
#include "share_wrapper.hpp"
#include "utils.hpp"
#include <curl/curl.h>
#include <memory>
#include <shared_mutex>
turna::ConnectionPool::ConnectionPool(const std::string & url , const InstanceConf  & instanceConf):shareObject(), instanceConf(instanceConf),this_ptr_(new ConnectionPool*(this)),pool_(){
    shareObject.setShare(CURL_LOCK_DATA_DNS);
    shareObject.setShare(CURL_LOCK_DATA_SSL_SESSION);
    for (int i =0 ; i< this->instanceConf.connection_count; i++ ){
        //curlObjects.push_back(CurlWrapper().setUrl(url).setUsrAgent(instanceConf.user_agent).setDNS(instanceConf.dns).setKeepConnection(true).setShareHandle(shareObject.getSharePtr()).setCurlVerbose());
        pool_.emplace(std::make_unique<CurlWrapper>());
        pool_.top()->setUrl(url).setUsrAgent(instanceConf.user_agent).setDNS(instanceConf.dns).setKeepConnection(true).setShareHandle(shareObject.getSharePtr()).setCurlVerbose().setRange({"0","1"}).setWriteFunction(turna::ignoreWriteStream);
        pool_.top()->executeCurl();
    }

}
void turna::ConnectionPool::notifyOne(){
    std::unique_lock<std::mutex> lock(wait_mutex);
    lock.unlock();
    cv.notify_one();
}
turna::ConnectionPool::ExternalDeleter::ExternalDeleter(std::weak_ptr<ConnectionPool* > pool):
pool_(pool){

}
void turna::ConnectionPool::ExternalDeleter::ExternalDeleter::operator()(CurlWrapper * ptr){
    if (auto pool_ptr = pool_.lock()) {
            try {
              (*pool_ptr.get())->add(std::unique_ptr<CurlWrapper>{ptr});
              (*pool_ptr.get())->notifyOne();
              return;
            } catch(...) {}
          }
          std::default_delete<CurlWrapper>{}(ptr);

}
void turna::ConnectionPool::add(std::unique_ptr<CurlWrapper> wrapper){
    pool_.push(std::move(wrapper));
}
turna::ConnectionPool::ptrType turna::ConnectionPool::acquireCurlWrapper(){
    if(!pool_.empty()){
        ptrType tmp(pool_.top().release(),
                        turna::ConnectionPool::ExternalDeleter{std::weak_ptr<ConnectionPool *>{this_ptr_}});
        pool_.pop();
        return std::move(tmp);
    }
    else{
        //wait for
            {
                std::unique_lock<std::mutex> lk(wait_mutex);
                cv.wait(lk);
            }
            return acquireCurlWrapper();

    }
}
