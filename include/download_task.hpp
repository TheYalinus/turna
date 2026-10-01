#ifndef  DOWNLOAD_TASK_HPP
#define DOWNLOAD_TASK_HPP
#include "download_conf.hpp"
#include "instance_conf.hpp"
#include <vector>
namespace turna {
    class DownloadTask{
        private:
            DownloadConf downloadConfig;
            InstanceConf instanceConfig;
        protected:
            DownloadTask(DownloadConf DownloadConfig , InstanceConf InstanceConf);
            virtual void finalize()=0;
            bool checkSumSha256();
    };
}
#endif
