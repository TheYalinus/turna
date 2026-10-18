#include "download_task.hpp"
#include "connection_pool.hpp"
#include "download_conf.hpp"
#include "exceptions.hpp"
#include "gather_info.hpp"
#include "instance_conf.hpp"
#include "part.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <string_view>
#include <thread>
#include <iostream>
#include <memory>
turna::DownloadTask::DownloadTask(std::shared_ptr<ConnectionPool> ConnectionPool , turna::DownloadConf DownloadConf,  InstanceConf InstanceConf) : connectionPool(ConnectionPool),  instanceConfig(InstanceConf) , downloadConfig(DownloadConf){
    if(!std::filesystem::exists(instanceConfig.task_location)){
        std::filesystem::create_directory(instanceConfig.task_location);
    }

    for (auto partx : *downloadConfig.getPartsData()){
        auto partpath = std::filesystem::path(instanceConfig.task_location / partx.fileName);
        if (std::filesystem::exists(partpath))
        {
            auto partnowsize= std::filesystem::file_size(partpath);
            partx.range.setFirst(partx.range.getFirst() + partnowsize);
            std::cout<<partx.range.getCurlRange()<<std::endl;
            if (partnowsize == partx.partSize) {
                partx.isCompleted =true;
            }
        }
        parts.push_back(std::make_unique<turna::Part>(partx.range,instanceConfig.task_location / partx.fileName,partx.isCompleted));
    }
}
bool turna::DownloadTask::checkSumSha256(){

}
turna::DownloadTask turna::DownloadTask::createNewTask(std::string_view url, unsigned int partCount , InstanceConf instanceConf, std::string_view sha256){
    if(std::filesystem::exists(instanceConf.task_location/"download.json" )){
        return loadTask(instanceConf ,url);
    }
    else{
        auto pool = std::make_shared<ConnectionPool>(std::string(url), instanceConf);
        auto wrapper = pool->acquireCurlWrapper();
        return {pool, gatherData(*wrapper.get(), std::string(url), partCount).setSHASig(sha256),instanceConf};
    }

}
turna::DownloadTask& turna::DownloadTask::startThreads(){
    for(auto &partx: parts ){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        threads.push_back(std::thread([&partx , this](){partx->downloadPart(connectionPool->acquireCurlWrapper().get());}));
    }
    return *this;
}
turna::DownloadTask& turna::DownloadTask::joinThreads(){
    for (auto &thread : threads) {
        thread.join();
    }
    return *this;
}
turna::DownloadTask& turna::DownloadTask::assembleFiles(){
    std::ofstream stream(instanceConfig.final_location / downloadConfig.getOriginalFileName());
    for (auto &partx : parts){
        stream<<partx->getReadStream()->rdbuf();
        stream.flush();

    }
    return *this;
}
turna::DownloadTask& turna::DownloadTask::saveConfig(){
    this->downloadConfig.saveTo(instanceConfig.task_location/"download.json");
    return *this;
}
turna::DownloadTask turna::DownloadTask::loadTask(InstanceConf instanceConf, std::string_view url)
{
    auto confjson = nlohmann::json(instanceConf.task_location / "download.json");
    auto downloadConfig= DownloadConf::LoadComplexConf(confjson);
    if(!url.empty()){
        downloadConfig.changeUrl(url);
    }
    auto pool = std::make_shared<ConnectionPool>(downloadConfig.getUrl(), instanceConf);
    auto wrapper = pool->acquireCurlWrapper();
    if (downloadConfig.is_acceptingHeaders()){
        auto newConf = _gatherHeadMethod(*wrapper.get(), downloadConfig.getUrl(), downloadConfig.getPartCount());
        if(downloadConfig.checkifStillValid(newConf))
            return {pool, downloadConfig,instanceConf};
        else
            throw BrokenUrlError("Url is broken, should be updated");
    }
    else {
        auto newConf = _gatherGetMethod(*wrapper.get(), downloadConfig.getUrl(), downloadConfig.getPartCount());
        if(downloadConfig.checkifStillValid(newConf))
            return {pool, downloadConfig,instanceConf};
        else
            throw BrokenUrlError("Url is broken, it needs to be updated");
    }
}
turna::DownloadTask& turna::DownloadTask::cleanFiles(){
    for (auto &partx : parts){
        partx->deleteFile();
    }
    std::filesystem::remove(instanceConfig.task_location/"download.json");
    return *this;
}
