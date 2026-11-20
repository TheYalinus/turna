#include "download_conf.hpp"
#include "download_task.hpp"
#include "instance_conf.hpp"
#include <turna.hpp>

int main(int argc, char *argv[]){
    if(argc<2)
        return -1;
    turna::InstanceConf conf;
    conf.task_location= argv[1];
    conf.user_agent ="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36";
    //you can specify any value of InstanceConf
    auto task = turna::DownloadTask::loadTask(conf); //load the task
    //if required you can refresh the url
    // auto task = turna::DownloadTask::loadTask(conf, url);
    // and dont forget to save config for next time
    // task.saveConfig();
    task.startThreads();
    //you are free here
    task.joinThreads();
    return 0;
}
