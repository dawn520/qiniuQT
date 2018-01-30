#include "qiniu.h"
#include "lib/qiniu/base.c"
#include "lib/qiniu/conf.c"
#include "lib/qiniu/http.c"
#include "iostream"

Qiniu::Qiniu(std::string sercertKeyIn, std::string AccessKeyIn)
{
    sercertKey = sercertKeyIn;
    accessKey = AccessKeyIn;

    Qiniu_Client client;
    QINIU_ACCESS_KEY = AccessKey;
    QINIU_SECRET_KEY = accessKey;
    Qiniu_Servend_Init(-1);                        /* 全局初始化函数，整个进程只需要调用一次 */
    Qiniu_Client_InitMacAuth(&client, 1024, NULL); /* HTTP客户端初始化。HTTP客户端是线程不安全的，不要在多个线程间共用 */
    Qiniu_Client_Cleanup(&client);                 /* 每个HTTP客户端使用完后释放 */
    Qiniu_Servend_Cleanup();                       /* 全局清理函数，只需要在进程退出时调用一次 */
}
