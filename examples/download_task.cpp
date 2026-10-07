#include "download_task.hpp"
#include <turna.hpp>
//Not completed
int main(){
    turna::DownloadTask task = turna::DownloadTask::createNewTask("https://fastly.mirror.pkgbuild.com/iso/2026.10.01/archlinux-2026.10.01-x86_64.iso", 1, {});
}
