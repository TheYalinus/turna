#include "download_conf.hpp"
turna::DownloadConf::DownloadConf(nlohmann::json json):
complex(true), url(json.at("url")), contentType(json.at("contentType")), originalFileName(json.at("originalFileName"))
,originalFileExtension(json.at("originalFileExtension")), originalFileSize(json.at("originalFileSize")), partSize(json.at("def_partSize")), partSizeRemainder(json.at("def_remainder"))
,partCount(json.at("partCount"))
{

}
turna::DownloadConf::DownloadConf(const std::string& url , unsigned int part_count):complex(true){

}
