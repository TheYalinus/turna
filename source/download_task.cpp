#include "download_task.hpp"
#include "connection_pool.hpp"
#include "download_conf.hpp"
#include "gather_info.hpp"
#include "instance_conf.hpp"
#include "part.hpp"
#include <chrono>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <thread>

#include <memory>
turna::DownloadTask::DownloadTask(std::shared_ptr<ConnectionPool> ConnectionPool , turna::DownloadConf DownloadConf,  InstanceConf InstanceConf) : connectionPool(ConnectionPool),  instanceConfig(InstanceConf) , downloadConfig(DownloadConf){
    if(!std::filesystem::exists(instanceConfig.task_location)){
        std::filesystem::create_directory(instanceConfig.task_location);
    }
    for (auto partx : *downloadConfig.getPartsData()){
        parts.push_back(std::make_unique<turna::Part>(partx.range,instanceConfig.task_location / partx.fileName));
    }
}
bool turna::DownloadTask::checkSumSha256(){

}
turna::DownloadTask turna::DownloadTask::createNewTask(std::string_view url, unsigned int partCount , InstanceConf instanceConf){
    auto pool = std::make_shared<ConnectionPool>(std::string(url), instanceConf);
    auto wrapper = pool->acquireCurlWrapper();
    return {pool, gatherData(*wrapper.get(), std::string(url), partCount),instanceConf};
}
void turna::DownloadTask::startThreads(){
    for(auto &partx: parts ){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        threads.push_back(std::thread([&partx , this](){partx->downloadPart(connectionPool->acquireCurlWrapper().get());}));
    }
}
void turna::DownloadTask::joinThreads(){
    for (auto &thread : threads) {
        thread.join();
    }
}
