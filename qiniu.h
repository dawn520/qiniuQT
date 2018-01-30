#ifndef QINIU_H
#define QINIU_H
#include "iostream"

class Qiniu
{
public:
    std::string sercertKey;
    std::string accessKey;
    std::string token;
    Qiniu(std::string sercertKeyIn, std::string AccessKeyIn);
};

#endif // QINIU_H
