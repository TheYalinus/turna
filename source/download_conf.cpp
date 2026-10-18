#include "download_conf.hpp"
#include "nlohmann/json_fwd.hpp"
#include "range_type.hpp"
#include "utils.hpp"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string>
#include <string_view>

turna::DownloadConf turna::DownloadConf::LoadComplexConf(nlohmann::json json){
    return turna::DownloadConf(json);
}
turna::DownloadConf turna::DownloadConf::NewComplexConf(unsigned int partCount, std::string_view url,  std::string_view contentType , std::string_view originalFileName, std::string_view originalFileExtension , unsigned long originalFileSize, bool header, std::string_view sha256){
    return turna::DownloadConf{partCount , url, contentType , originalFileName , originalFileExtension , originalFileSize , true , header};
}
turna::DownloadConf turna::DownloadConf::NewSimpleConf(std::string_view url){
    return {url};
}
turna::DownloadConf::DownloadConf(nlohmann::json json): url(json.at("url")),sha256(json.at("sha256")), contentType(json.at("contentType")), originalFileName(json.at("originalFileName"))
,originalFileExtension(json.at("originalFileExtension")), originalFileSize(json.at("originalFileSize")), partSize(json.at("def_partSize")), partSizeRemainder(json.at("def_remainder")),complex(true)
,partCount(json.at("partCount"))
{
    for (auto part: json["parts"]){
        std::string range =part["pRange"];
        this->parts.push_back({
            RangeType(range),
            part["pSize"],
            part["pId"],
            part["pFileName"]
        });
    }
}
turna::DownloadConf::DownloadConf( unsigned int partCount, std::string_view url, std::string_view contentType , std::string_view originalFileName, std::string_view originalFileExtension , unsigned long originalFileSize,bool complex,bool header, std::string_view sha256):
url(url),sha256(sha256), partCount(partCount), contentType(contentType) ,originalFileSize(originalFileSize), originalFileExtension(originalFileExtension), originalFileName(originalFileName), partSize(originalFileSize / partCount), partSizeRemainder(originalFileSize %partSize) , complex(complex), header(header){
    for(int i =0; i< partCount ; i++){
        RangeType buff("","");
        if(i<partCount-1)
            {
                    buff.setFirst(std::to_string(i*partSize));
                    buff.setSecond(std::to_string(((i+1)*partSize)-1));
                    this->parts.push_back({
                        buff,
                        partSize,
                        i,
                        getTempFileNameforPart(i, this->originalFileName)
                    });
            }
        else {
                    buff.setFirst(std::to_string(i*partSize));
                    this->parts.push_back({
                        buff,
                        partSize+this->getPartSizeRemainder(),
                        i,
                        getTempFileNameforPart(i, this->originalFileName)
                    });
        }
    }
}
bool turna::DownloadConf::checkifStillValid(turna::DownloadConf& conf)
{
    if(this->getOriginalFileName() != conf.getOriginalFileName())
        return false;
    else if (this->getContentType() != conf.getContentType())
        return false;
    else
        return true;
}
std::string turna::DownloadConf::getContentType(){
    return this->contentType;
}
std::string turna::DownloadConf::getOriginalFileName(){
    return this->originalFileName;
}
std::string turna::DownloadConf::getSHASig(){
    return this->sha256;
}
std::string turna::DownloadConf::getUrl(){
    return this->url;
}
std::string turna::DownloadConf::getOriginalFileExtension(){
    return this->originalFileExtension;
}
unsigned int turna::DownloadConf::getPartCount(){
    return this->partCount;
}
bool turna::DownloadConf::is_complex(){
    return this->complex;
}
bool turna::DownloadConf::is_acceptingHeaders(){
    return this->header;
}
unsigned long turna::DownloadConf::getOriginalFileSize(){
    return this->originalFileSize;
}
unsigned long turna::DownloadConf::getPartSizeRemainder(){
    return this->partSizeRemainder;
}
turna::DownloadConf& turna::DownloadConf::saveTo(std::filesystem::path path){
    nlohmann::json json;
    json["version"]="0.1.1";
    json["complex"]=is_complex();
    json["header"]=is_acceptingHeaders();
    json["parts"]={};
    json["originalFileExtension"]=getOriginalFileExtension();
    json["originalFileName"]=getOriginalFileName();
    json["originalFileSize"]=getOriginalFileSize();
    json["contentType"]= getContentType();
    json["url"]= getUrl();
    json["sha256"]= getSHASig();
    json["partCount"]=getPartCount();
    json["def_remainder"]=getPartSizeRemainder();
    json["def_partSize"]=getPartSize();
    for(auto &part : *getPartsData()){
        json["parts"][part.id]={};
        json["parts"][part.id]["pSize"]= part.partSize;
        json["parts"][part.id]["pFileName"]=part.fileName;
        json["parts"][part.id]["pRange"]=part.range.getCurlRange();
        json["parts"][part.id]["pId"]= part.id;
    }
    std::ofstream stream(path);
    stream<<std::setw(4)<<json<<std::endl;
    stream.close();
    return *this;
}
turna::DownloadConf& turna::DownloadConf::setSHASig(std::string_view sha256){
    this->sha256 = sha256;
    return *this;
}
unsigned long turna::DownloadConf::getPartSize(){
    return this->partSize;
}
std::vector<turna::partData> * turna::DownloadConf::getPartsData(){
    return &this->parts;
}
turna::DownloadConf& turna::DownloadConf::changeUrl(std::string_view url){
    this->url = url;
    return *this;
}
