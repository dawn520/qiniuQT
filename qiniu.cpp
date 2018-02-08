#include "qiniu.h"
#include "iostream"
#include "lib/qiniu/include/qiniu/base.h"
#include "lib/qiniu/include/qiniu/conf.h"
#include "lib/qiniu/include/qiniu/http.h"

#include "lib/qiniu/include/qiniu/rs.h"
#include "lib/qiniu/include/qiniu/io.h"
#include "lib/qiniu/include/qiniu/rsf.h"



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

qiniuReturn Qiniu::uploadFile(std::string bucketName,std::string keyName, std::string fileName,int location) {
    Qiniu_Global_Init(-1);
    Qiniu_Mac mac;
    mac.accessKey = accessKey.data();
    mac.secretKey = sercertKey.data();
    const char *bucket = bucketName.data();
    const char *key = keyName.data();
    const char *localFile = fileName.data();
    Qiniu_Io_PutRet putRet;
    Qiniu_Client client;
    Qiniu_RS_PutPolicy putPolicy;
    Qiniu_Io_PutExtra putExtra;
    Qiniu_Zero(putPolicy);
    Qiniu_Zero(putExtra);
    putPolicy.scope = bucket;
    char *uptoken = Qiniu_RS_PutPolicy_Token(&putPolicy, &mac);
    switch (location) {
    default:
    case 0:
        Qiniu_Use_Zone_Huadong(Qiniu_True);
        break;
    case 1:
        Qiniu_Use_Zone_Huabei(Qiniu_True);
        break;
    case 2:
        Qiniu_Use_Zone_Huanan(Qiniu_True);
        break;
    case 3:
        Qiniu_Use_Zone_Beimei(Qiniu_True);
        break;
    }
    printf("the location chosen is %d.\n", location);
    Qiniu_Client_InitMacAuth(&client, 1024, &mac);

    Qiniu_Error error = Qiniu_Io_PutFile(&client, &putRet, uptoken, key, localFile, &putExtra);
    qiniuReturn qReturn;
    if (error.code != 200) {
        printf("upload file %s:%s error.\n", bucket, key);
        debug(&client, error);
    }
    else {
        /*200, 正确返回了, 你可以通过statRet变量查询一些关于这个文件的信息*/
        printf("upload file %s:%s success.\n\n", bucket, key);
        printf("key:\t%s\n", putRet.key);
        printf("hash:\t%s\n", putRet.hash);
    }
    Qiniu_Free(uptoken);
    Qiniu_Client_Cleanup(&client);

    qReturn.code = error.code;
    qReturn.message = error.message;
    return qReturn;
}

//void Qiniu::getBucketsList() {
//    Qiniu_Global_Init(-1);
//
//    Qiniu_RSF_ListRet listRet;
//    Qiniu_Client client;
//
//    const char *accessKey = "0W_4wL_5ldYISAnty8M39hFQ1f7iN-F7vU1Vqpvo";
//    const char *secretKey = "n3MtMSgmSucSfygNEx3CHuP_6AUUPXzUK64dlKiU";
//    const char *bucket = "test";
//    const char *prefix = "";
//    const char *delimiter = "/";
//    const char *marker = "s";
//    const char *nextMarker = marker;
//    Qiniu_Bool isNewMarker = Qiniu_False;
//    int limit = 10;
//    int i;
//
//    Qiniu_Mac mac;
//    mac.accessKey = accessKey;
//    mac.secretKey = secretKey;
//
//    char **commonPrefixes = NULL;
//    Qiniu_RSF_ListItem *items = NULL;
//
//    do {
//        //init
//        Qiniu_Client_InitMacAuth(&client, 1024, &mac);
//        Qiniu_Error error = Qiniu_RSF_ListFiles(&client, &listRet, bucket, prefix, delimiter, nextMarker, limit);
//
//        if (error.code != 200) {
//            printf("list files of bucket %s error.\n", bucket);
//            debug(&client, error);
//            nextMarker = "";
//        }
//        else {
//            /*200, 正确返回了, 你可以通过listRet变量查询文件列表信息*/
//            printf("list files of bucket %s success.\n\n", bucket);
//
//            //check next marker
//            if (isNewMarker == Qiniu_True) {
//                delete(nextMarker);
//            }
//
//            if (listRet.marker && listRet.marker != '\0') {
//                nextMarker = strdup(listRet.marker);
//                isNewMarker = Qiniu_True;
//            }
//            else {
//                nextMarker = NULL;
//            }
//            printf("next marker: %s\n", nextMarker);
//
//            //common prefixes
//            commonPrefixes = listRet.commonPrefixes;
//            for (i = 0; i < listRet.commonPrefixesCount; i++) {
//                printf("commonPrefix: %s\n", *commonPrefixes);
//                ++commonPrefixes;
//            }
//
//            //items
//            items = listRet.items;
//            for (i = 0; i < listRet.itemsCount; i++) {
//                Qiniu_RSF_ListItem item = listRet.items[i];
//                printf("key: %s, hash: %s, fsize: %lld, mime: %s, putTime: %lld, endUser: %s, type: %lld\n",
//                    item.key, item.hash, item.fsize, item.mimeType, item.putTime, item.endUser, item.type);
//            }
//
//            //free
//            if (listRet.commonPrefixes != NULL) {
//                Qiniu_Free(listRet.commonPrefixes);
//            }
//            if (listRet.items != NULL) {
//                Qiniu_Free(listRet.items);
//            }
//
//            Qiniu_Zero(listRet);
//        }
//
//        Qiniu_Client_Cleanup(&client);
//    } while (nextMarker && nextMarker != '\0');
//}

//void Qiniu::getFilesList() {
//    Qiniu_Global_Init(-1);

//    Qiniu_RSF_ListRet listRet;
//    Qiniu_Client client;

//    const char *accessKey = getenv("QINIU_ACCESS_KEY");
//    const char *secretKey = getenv("QINIU_SECRET_KEY");
//    const char *bucket = getenv("QINIU_TEST_BUCKET");
//    const char *prefix = "";
//    const char *delimiter = "/";
//    const char *marker = "";
//    int limit = 100;
//    int i;

//    Qiniu_Mac mac;
//    mac.accessKey = accessKey;
//    mac.secretKey = secretKey;

//    char **commonPrefixes = NULL;
//    Qiniu_RSF_ListItem *items = NULL;

//    //init
//    Qiniu_Client_InitMacAuth(&client, 1024, &mac);
//    Qiniu_Error error = Qiniu_RSF_ListFiles(&client, &listRet, bucket, prefix, delimiter, marker, limit);
//    if (error.code != 200) {
//        printf("list files of bucket %s error.\n", bucket);
//        debug(&client, error);
//    }
//    else {
//        /*200, 正确返回了, 你可以通过listRet变量查询文件列表信息*/
//        printf("list files of bucket %s success.\n\n", bucket);
//        //marker
//        printf("next marker: %s\n", listRet.marker);

//        //common prefixes
//        commonPrefixes = listRet.commonPrefixes;
//        for (i = 0; i < listRet.commonPrefixesCount; i++) {
//            printf("commonPrefix: %s\n", *commonPrefixes);
//            ++commonPrefixes;
//        }

//        //items
//        items = listRet.items;
//        for (i = 0; i < listRet.itemsCount; i++) {
//            Qiniu_RSF_ListItem item = listRet.items[i];
//            printf("key: %s, hash: %s, fsize: %lld, mime: %s, putTime: %lld, endUser: %s, type: %lld\n",
//                item.key, item.hash, item.fsize, item.mimeType, item.putTime, item.endUser, item.type);
//        }

//        //free
//        if (listRet.commonPrefixes != NULL) {
//            Qiniu_Free(listRet.commonPrefixes);
//        }
//        if (listRet.items != NULL) {
//            Qiniu_Free(listRet.items);
//        }
//    }

//    Qiniu_Client_Cleanup(&client);
//}

void Qiniu::debug(Qiniu_Client* client, Qiniu_Error err)
{
    printf("\nerror code: %d, message: %s\n", err.code, err.message);
    printf("respose header:\n%s", Qiniu_Buffer_CStr(&client->respHeader));
    printf("respose body:\n%s", Qiniu_Buffer_CStr(&client->b));
}


