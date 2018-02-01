#include "qiniu.h"
#include "iostream"
#include "lib/qiniu/include/qiniu/base.h";
#include "lib/qiniu/include/qiniu/conf.h";
#include "lib/qiniu/include/qiniu/http.h";

#include "lib/qiniu/include/qiniu/rs.h";
#include "lib/qiniu/include/qiniu/io.h";



Qiniu::Qiniu(std::string sercertKeyIn, std::string AccessKeyIn)
{
    sercertKey = sercertKeyIn;
    accessKey = AccessKeyIn;

//    Qiniu_Client client;
//    QINIU_ACCESS_KEY = sercertKey.data();;
//    QINIU_SECRET_KEY = accessKey.data();;
//    Qiniu_Servend_Init(-1);                        /* 全局初始化函数，整个进程只需要调用一次 */
//    Qiniu_Client_InitMacAuth(&client, 1024, NULL); /* HTTP客户端初始化。HTTP客户端是线程不安全的，不要在多个线程间共用 */
//    Qiniu_Client_Cleanup(&client);                 /* 每个HTTP客户端使用完后释放 */
//    Qiniu_Servend_Cleanup();                       /* 全局清理函数，只需要在进程退出时调用一次 */
}

void Qiniu::uploadFile(){
    Qiniu_Global_Init(-1);
    Qiniu_Mac mac;
//    mac.accessKey = accessKey.data();
//    mac.secretKey = sercertKey.data();
    mac.accessKey = "0W_4wL_5ldYISAnty8M39hFQ1f7iN-F7vU1Vqpvo";
    mac.secretKey = "n3MtMSgmSucSfygNEx3CHuP_6AUUPXzUK64dlKiU";
    const char *bucket = "test";
    const char *key = "1541515304366.jpg";
    const char *localFile = "/Users/xixi/Desktop/1541515304366_.pic_hd.jpg";
    Qiniu_Io_PutRet putRet;
    Qiniu_Client client;
    Qiniu_RS_PutPolicy putPolicy;
    Qiniu_Io_PutExtra putExtra;
    Qiniu_Zero(putPolicy);
    Qiniu_Zero(putExtra);
    putPolicy.scope = bucket;
    char *uptoken = Qiniu_RS_PutPolicy_Token(&putPolicy, &mac);
    //设置机房域名
    //Qiniu_Use_Zone_Beimei(Qiniu_False);
    //Qiniu_Use_Zone_Huabei(Qiniu_True);
//    Qiniu_Use_Zone_Huadong(Qiniu_False);
    Qiniu_Use_Zone_Huanan(Qiniu_True);
    Qiniu_Client_InitMacAuth(&client, 1024, &mac);
    Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uptoken, key, localFile, &putExtra);
    if (error.code != 200) {
      printf("upload file %s:%s error.\n", bucket, key);
      debug(&client, error);
    } else {
      /*200, 正确返回了, 你可以通过statRet变量查询一些关于这个文件的信息*/
      printf("upload file %s:%s success.\n\n", bucket, key);
      printf("key:\t%s\n",putRet.key);
      printf("hash:\t%s\n", putRet.hash);
    }
    Qiniu_Free(uptoken);
    Qiniu_Client_Cleanup(&client);
}

void Qiniu::debug(Qiniu_Client* client, Qiniu_Error err)
{
    printf("\nerror code: %d, message: %s\n", err.code, err.message);
    printf("respose header:\n%s", Qiniu_Buffer_CStr(&client->respHeader));
    printf("respose body:\n%s", Qiniu_Buffer_CStr(&client->b));
}
