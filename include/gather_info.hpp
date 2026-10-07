#ifndef GATHER_INFO_HPP
#define GATHER_INFO_HPP
#include "curl_wrapper.hpp"
#include "download_conf.hpp"
#include <cstddef>
namespace turna {
    turna::DownloadConf gatherData(turna::CurlWrapper &, const std::string & url,  unsigned int partCount);
    turna::DownloadConf _gatherHeadMethod(turna::CurlWrapper & , const std::string & url,  unsigned int partCount);
    turna::DownloadConf _gatherGetMethod(turna::CurlWrapper &, const  std::string & url, unsigned int partCount);
    size_t _dummyWriteCallback(char *data, size_t size, size_t nmemb, void *clientp);
}

#endif
