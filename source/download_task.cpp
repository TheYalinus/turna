#include "download_task.hpp"
#include "connection_pool.hpp"
#include "download_conf.hpp"
#include "gather_info.hpp"
#include "instance_conf.hpp"
#include <memory>
#include <string>
#include <string_view>
turna::DownloadTask::DownloadTask(std::shared_ptr<ConnectionPool> ConnectionPool , turna::DownloadConf DownloadConf,  InstanceConf InstanceConf) : connectionPool(ConnectionPool),  instanceConfig(InstanceConf) , downloadConfig(DownloadConf){

}
bool turna::DownloadTask::checkSumSha256(){

}
turna::DownloadTask turna::DownloadTask::createNewTask(std::string_view url, unsigned int partCount , InstanceConf instanceConf){
    auto pool = std::make_shared<ConnectionPool>(std::string(url), instanceConf);
    auto wrapper = pool->acquireCurlWrapper();
    return {pool, gatherData(*wrapper.get(), std::string(url), partCount),instanceConf};
}
