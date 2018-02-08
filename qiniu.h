#ifndef QINIU_H
#define QINIU_H
#include "iostream"
#include "lib/qiniu/include/qiniu/base.h"
#include "lib/qiniu/include/qiniu/conf.h"
#include "lib/qiniu/include/qiniu/http.h"

typedef struct qiniuReturn
{
    int code;
    const char * message;
}qiniuReturn;

class Qiniu
{
public:
    std::string sercertKey;
    std::string accessKey;
    std::string token;
    Qiniu(std::string sercertKeyIn, std::string AccessKeyIn);

    qiniuReturn uploadFile(std::string bucketName,std::string keyName, std::string fileName, int location);
    void getBucketsList();
    void getFilesList();
    void debug(Qiniu_Client *client, Qiniu_Error err);
    wchar_t CN2Unicode(char *input);
    char *WcharToChar(const wchar_t *wp);
};

#endif // QINIU_H
