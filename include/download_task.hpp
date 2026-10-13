#ifndef  DOWNLOAD_TASK_HPP
#define DOWNLOAD_TASK_HPP
#include "connection_pool.hpp"
#include "download_conf.hpp"
#include "instance_conf.hpp"
#include "part.hpp"
#include <memory>
#include <thread>
#include <vector>
namespace turna {
    class DownloadTask{
        private:
            DownloadConf downloadConfig;
            InstanceConf instanceConfig;
            std::shared_ptr<ConnectionPool> connectionPool;
            std::vector<std::unique_ptr<Part>> parts;
            std::vector<std::thread> threads;
        protected:
            DownloadTask(std::shared_ptr<ConnectionPool> ConnectionPool, DownloadConf DownloadConf,  InstanceConf InstanceConf);
        public:
            static DownloadTask createNewTask(std::string_view url, unsigned int partCount , InstanceConf instanceConf);
            void startThreads();
            void joinThreads();
            bool checkSumSha256();
    };
}
#endif
