#ifndef CONNECTION_POOL_HPP
#define CONNECTION_POOL_HPP
#include "curl_wrapper.hpp"
#include "instance_conf.hpp"
#include "share_wrapper.hpp"
#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>
#include <stack>
namespace turna {
    class ConnectionPool{
        public:
            ConnectionPool(const std::string & url, const InstanceConf &instanceConf);
        private:
            //https://stackoverflow.com/a/27837534
            struct ExternalDeleter{
                public:
                    explicit ExternalDeleter(std::weak_ptr<ConnectionPool* > pool);
                    void operator() (CurlWrapper * ptr);
                private:
                    std::weak_ptr<ConnectionPool* > pool_;
            };
            std::mutex wait_mutex;
            std::condition_variable cv;
            struct InstanceConf instanceConf;
            class ShareWrapper shareObject;
            std::shared_ptr<ConnectionPool *> this_ptr_;
            std::stack<std::unique_ptr<CurlWrapper>>pool_;
        protected:
            void notifyOne();
        public:
            using ptrType = std::unique_ptr<CurlWrapper ,ExternalDeleter>;
            void add(std::unique_ptr<CurlWrapper> wrapper);
            ptrType acquireCurlWrapper();
    };
}
#endif
