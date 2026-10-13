#include "download_task.hpp"
#include <turna.hpp>
//Not completed
int main(){
    turna::InstanceConf conf {}; //A config that keeps instance-specific things like dns and user-agents
    conf.connection_count= 2 ;
    conf.user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36"; //you'll need this somehow
    turna::DownloadTask task = turna::DownloadTask::createNewTask("https://fastly.mirror.pkgbuild.com/iso/2026.10.01/archlinux-2026.10.01-x86_64.iso", 4, conf);
    task.startThreads();
    task.joinThreads();
}
