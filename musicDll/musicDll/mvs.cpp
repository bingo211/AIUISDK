#include "mvs.h"
#include <iostream>
#include <windows.h>
#include <process.h>
#include <fstream>
#include "picojson.h"
#include "utils.h"

mvs::mvs()
{
    mMutex = CreateMutex(NULL, FALSE, NULL);
}

mvs::~mvs()
{
    destroySession();
    CloseHandle(mMutex);
}

void mvs::globalInit()
{
    INT rc;
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        return ;
    }
}

void mvs::globalUninit()
{
    WSACleanup();
}

void mvs::startConnection(const char *url, _ConnectionCallback cb, _HandlerMessageCallback hb)
{
   destroySession();
   if (url == NULL  || cb == NULL || hb == NULL){
        return ;
   }
   done = false;
   if (thread_hdl_ == NULL) {
       thread_hdl_ = (HANDLE)_beginthreadex(NULL, 0, WriteProc, (LPVOID) this, 0,  &thread_id_);
   }

   sUrl = url;
   this->__cb = cb;
   this->__hb = hb;

   return;
}

/**
 * @brief mvs::sendData   aiui输入文本
 * @param text  文本格式
 *
{
    "common": {},
    "business": {
        "mixType": "aiui",
        "interrupt": false // true打断，立即清空所有输入， false/null 持续合成
    },
    "data": {
        "type": "text",
        "text": "北京今天天气怎么样"
    }
}
 *
 */
void mvs::sendData(const string &text, bool interrupt)
{
   //tojson
    picojson::value json;
    json.set<picojson::object>(picojson::object());
    //common
    json.get<picojson::object>()["common"].set<picojson::object>(picojson::object());
    //business
    json.get<picojson::object>()["business"].set<picojson::object>(picojson::object());
    json.get<picojson::object>()["business"].get<picojson::object>()["mixType"] = picojson::value(std::string("aiui"));
    json.get<picojson::object>()["business"].get<picojson::object>()["interrupt"] = picojson::value(bool(interrupt));
    //data
    json.get<picojson::object>()["data"].set<picojson::object>(picojson::object());
    json.get<picojson::object>()["data"].get<picojson::object>()["type"] = picojson::value(std::string("text"));
    json.get<picojson::object>()["data"].get<picojson::object>()["text"] = picojson::value(std::string(text));

    std::string sjson = json.serialize();
    WaitForSingleObject(mMutex, INFINITE);
    if (ws)
        ws->send(sjson);
    ReleaseMutex(mMutex);
}

/**
 * @brief mvs::sendAudioData   仅支持16k16bit
 * @param audio
 * @param interrupt
 *
 */
void mvs::sendAudioData(const string &audio, bool interrupt)
{
    //tojson
     picojson::value json;
     json.set<picojson::object>(picojson::object());
     //common
     json.get<picojson::object>()["common"].set<picojson::object>(picojson::object());
     //business
     json.get<picojson::object>()["business"].set<picojson::object>(picojson::object());
     json.get<picojson::object>()["business"].get<picojson::object>()["mixType"] = picojson::value(std::string("audio"));
     json.get<picojson::object>()["business"].get<picojson::object>()["interrupt"] = picojson::value(bool(interrupt));

     //data
     json.get<picojson::object>()["data"].set<picojson::object>(picojson::object());
     //读取本地文件
     ifstream ifs (audio);
     if (ifs.fail()){
         return;
     }
     stringstream buffer;
     buffer<< ifs.rdbuf();
     string contents = buffer.str();
     //进行base64编码
     string content_base64 = base64::encode(contents);
     ifs.close();

     //删除文件
     std::remove(audio.data());
     json.get<picojson::object>()["data"].get<picojson::object>()["audio"] = picojson::value(content_base64);

     std::string sjson = json.serialize();
     WaitForSingleObject(mMutex, INFINITE);
     if (ws)
         ws->send(sjson);
     ReleaseMutex(mMutex);
}

/**
 * @brief mvs::sendRawData
 * @param audio
 * @param interrupt   是否中断
 * {
    "common": {},
    "business": {
        "mixType": "aiui",
        "interrupt": false
    },
    "data": {
        "type": "raw",
        "header": {
            "X-CurTime": 1586763686,
            "X-Param": "AAAAAAAAAA....",
            "X-Appid": "abcdefg",
            "X-CheckSum": "2a9bc451af4e6b3a60070d243308653b",
        },
        "bodyBase64": "AAAAAAAA....."
    }
}
 */
void mvs::sendRawData(const string &raw, bool interrupt)
{
    picojson::value json;
    json.set<picojson::object>(picojson::object());
    //common
    json.get<picojson::object>()["common"].set<picojson::object>(picojson::object());
    //business
    json.get<picojson::object>()["business"].set<picojson::object>(picojson::object());
    json.get<picojson::object>()["business"].get<picojson::object>()["mixType"] = picojson::value(std::string("aiui"));
    json.get<picojson::object>()["business"].get<picojson::object>()["interrupt"] = picojson::value(bool(interrupt));

    //data
    json.get<picojson::object>()["data"].set<picojson::object>(picojson::object());
    json.get<picojson::object>()["data"].get<picojson::object>()["type"] = picojson::value(std::string("raw"));
    //bodybase64
    json.get<picojson::object>()["data"].get<picojson::object>()["bodyBase64"] = picojson::value(base64::encode(raw));
    //header
    json.get<picojson::object>()["data"].get<picojson::object>()["header"].set<picojson::object>(picojson::object());
    //timestamp
    int64_t timestamp = getTimeStamp2();
    json.get<picojson::object>()["data"].get<picojson::object>()["header"].get<picojson::object>()["X-CurTime"] = picojson::value(double(timestamp));
    //appid
    json.get<picojson::object>()["data"].get<picojson::object>()["header"].get<picojson::object>()["X-Appid"] = picojson::value(appid);
    //params https://doc.iflyos.cn/aiui/sdk/more_doc/webapi/summary.html#%E8%AF%B7%E6%B1%82%E5%8F%82%E6%95%B0
    picojson::value xp;
    xp.set<picojson::object>(picojson::object());
    xp.get<picojson::object>()["scene"] = picojson::value(skills);
    xp.get<picojson::object>()["data_type"] = picojson::value("text");
    xp.get<picojson::object>()["auth_id"] = picojson::value(auth_id);
    std::string __params =  base64::encode(xp.serialize());
    json.get<picojson::object>()["data"].get<picojson::object>()["header"].get<picojson::object>()["X-Param"] = picojson::value(__params);

    //token
    std::string __token = token2(timestamp,__params);
    json.get<picojson::object>()["data"].get<picojson::object>()["header"].get<picojson::object>()["X-CheckSum"] = picojson::value(__token);

    std::string sjson = json.serialize();

    WaitForSingleObject(mMutex, INFINITE);
    if (ws)
        ws->send(sjson);
    ReleaseMutex(mMutex);
}

void mvs::destroySession()
{
    done = true;
    WaitForSingleObject(thread_hdl_,INFINITE);
    CloseHandle(thread_hdl_);
    thread_hdl_ = NULL;
}

bool mvs::threadLoop()
{
    while (!done) {
           if (ws != NULL)
           {
               if (ws->getReadyState() != WebSocket::CLOSED)
               {
                   WaitForSingleObject(mMutex, INFINITE);
                   ws->poll(0);
                   ws->dispatch(this->__hb);
                   ReleaseMutex(mMutex);
               }

               if (ws->getReadyState() == WebSocket::CLOSED)
               {
                   // 连接断开重连
                   delete ws;
                   ws = NULL;
                   ws = WebSocket::from_url(sUrl);
                   if (ws != NULL && ws->getReadyState() == WebSocket::OPEN)
                       this->__cb(true);
                   else
                       this->__cb(false);
               }
           }
           else
           {
               ws = WebSocket::from_url(sUrl);
               if (ws != NULL && ws->getReadyState() == WebSocket::OPEN)
                   this->__cb(true);
               else
                   this->__cb(false);
           }
          Sleep(10);
       }

       if (ws)
       {
           ws->close();
           ws->poll(0);
           delete ws;
           ws = NULL;
       }
       return true;
}


unsigned int __stdcall mvs::WriteProc(void * paramptr)
{
    mvs * self = (mvs *)paramptr;
    self->threadLoop();
    return 0;
}
