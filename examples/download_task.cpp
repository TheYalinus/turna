#include "download_task.hpp"
#include <turna.hpp>
//Not completed
int main(){
    turna::InstanceConf conf {}; //A config that keeps instance-specific things like dns and user-agents
    //in instanceConf you can specify task directory, by default it generates a file name based on current date-time
    //if you specify an already existing location, it will check for a download.json file
    // if found, it will automatically resume your download task
    // but sometimes urls get broken, and system automatically checks for this, and if this happens you'll need to change your url
    // automatically if you load an existing download with createNewTask it automatically passes the url which given as argument to loadTask
    // for loadTask function take a look at examples/load_task.cpp
    //
    // for next time, if you want to, you can change values in here without causing any problems
    // eg. you may want to change user agent to another one, you can change it without corrupting anything
    conf.connection_count= 3 ; // initalizing too many connections may cause problems
    conf.user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36"; //you'll need this somehow
    turna::DownloadTask task = turna::DownloadTask::createNewTask("https://fastly.mirror.pkgbuild.com/iso/2026.10.01/archlinux-2026.10.01-x86_64.iso", 4, conf, "aaa");
    task.saveConfig();//save the config into a download.json file, with this you can resume your download
    task.startThreads();
    //you can do anything else here
    task.joinThreads(); // dont forget to join threads, thus you can ensure program will wait for the each thread to finish before ending
    task.assembleFiles(); //assemble parts into one part which bind them all together
    task.cleanFiles(); //delete temporary part files and download.json file
}
