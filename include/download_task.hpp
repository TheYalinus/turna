#ifndef  DOWNLOAD_TASK_HPP
#define DOWNLOAD_TASK_HPP
#include "connection_pool.hpp"
#include "download_conf.hpp"
#include "instance_conf.hpp"
#include <memory>
#include <vector>
namespace turna {
    class DownloadTask{
        private:
            DownloadConf downloadConfig;
            InstanceConf instanceConfig;
            std::shared_ptr<ConnectionPool> connectionPool;
        protected:
            DownloadTask(std::shared_ptr<ConnectionPool> ConnectionPool, DownloadConf DownloadConf,  InstanceConf InstanceConf);
        public:
            static DownloadTask createNewTask(std::string_view url, unsigned int partCount , InstanceConf instanceConf);
            bool checkSumSha256();
    };
}
#endif
