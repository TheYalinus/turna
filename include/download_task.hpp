#ifndef  DOWNLOAD_TASK_HPP
#define DOWNLOAD_TASK_HPP
#include "connection_pool.hpp"
#include "download_conf.hpp"
#include "instance_conf.hpp"
#include "part.hpp"
#include <memory>
#include <string_view>
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
        public:
            DownloadTask(std::shared_ptr<ConnectionPool> ConnectionPool, DownloadConf DownloadConf,  InstanceConf InstanceConf);
            static DownloadTask createNewTask(std::string_view url, unsigned int partCount , InstanceConf instanceConf, std::string_view sha256="");
            static DownloadTask loadTask(InstanceConf ,std::string_view  url ="");
            DownloadTask& startThreads();
            DownloadTask& joinThreads();
            bool checkSumSha256();
            DownloadTask& assembleFiles();
            DownloadTask& cleanFiles();
            DownloadTask& saveConfig();
    };
}
#endif
