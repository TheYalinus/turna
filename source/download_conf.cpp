#include "download_conf.hpp"
#include <string_view>
turna::DownloadConfComplex::DownloadConfComplex(nlohmann::json json): DownloadConf(json.at("url")), contentType(json.at("contentType")), originalFileName(json.at("originalFileName"))
,originalFileExtension(json.at("originalFileExtension")), originalFileSize(json.at("originalFileSize")), partSize(json.at("def_partSize")), partSizeRemainder(json.at("def_remainder"))
,partCount(json.at("partCount"))
{

}
turna::DownloadConfComplex::DownloadConfComplex( unsigned int partCount, std::string_view url, std::string_view contentType , std::string_view originalFileName, std::string_view originalFileExtension , unsigned long originalFileSize):
DownloadConf(url), partCount(partCount), contentType(contentType) ,originalFileSize(originalFileSize), originalFileExtension(originalFileExtension), originalFileName(originalFileName), partSize(originalFileSize / partCount), partSizeRemainder(originalFileSize %partSize){

}
