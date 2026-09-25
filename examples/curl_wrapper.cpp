#include <turna.hpp>
int main(int argc , char * argv[]){
    if(argc< 2)
        return -1;
    turna::CurlWrapper wrapper;
    wrapper.setUrl(argv[1]);
    wrapper.setFollowRedirects();
    wrapper.setUsrAgent("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/153.0.0.0 Safari/537.36");
    wrapper.executeCurl();
    return 0;
}
