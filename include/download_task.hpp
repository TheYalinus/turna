#ifndef  DOWNLOAD_TASK_HPP
#define DOWNLOAD_TASK_HPP
#include "download_conf.hpp"
#include "instance_conf.hpp"
#include <vector>
namespace turna {
    class DownloadTask{
        public:
            DownloadTask(DownloadConf DownloadConfig , InstanceConf InstanceConf);
        private:
            DownloadConf downloadConfig;
            InstanceConf instanceConfig;
            virtual void finalize()=0;
            virtual void checkSumSha256();
            virtual void checkSumMd5();
    };
}
#endif
