#ifndef CONNECTION_POOL_HPP
#define CONNECTION_POOL_HPP
#include "curl_wrapper.hpp"
#include "instance_conf.hpp"
#include "share_wrapper.hpp"
#include <condition_variable>
#include <memory>
#include <shared_mutex>
#include <vector>
namespace turna {
    class ConnectionPool{
        public:
            ConnectionPool(std::string & url, InstanceConf & instanceConf);
        private:
            std::shared_mutex wait_mutex;
            std::condition_variable cv;
            std::vector<std::shared_ptr<CurlWrapper>> curlObjects;
            struct InstanceConf instanceConf;
            ShareWrapper shareObject;
    };
}
#endif
