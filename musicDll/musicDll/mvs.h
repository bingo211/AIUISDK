#ifndef MVS_H
#define MVS_H

#include <string>
#include <windows.h>
#include "easywsclient.hpp"

using namespace  std;
using easywsclient::WebSocket;

typedef    void(*_HandlerMessageCallback)(const string &data);
typedef    void(*_ConnectionCallback)(bool success);

//保持长连接

class mvs
{
public:
    mvs();
    virtual ~mvs();
    static void globalInit();
    static void globalUninit();
    /**
     * @brief startConnection
     * @param url
     * @param cb 连接状态回调
     * @param hb   数据回调
     */
    void startConnection(const char* url, _ConnectionCallback cb , _HandlerMessageCallback hb);
    /**
     * @brief sendData   发送文本内容到虚拟形象服务
     * @param text 推送文本内容
     * @param interrupt   是否打断，默认为非打断
     */
    void sendData(const std::string &text,bool interrupt = false);
    /**
     * @brief sendAudioData  传递音频到虚拟形象
     * @param audio   音频数据
     * @param interrupt   是否打断
     */
    void sendAudioData(const std::string &audio, bool interrupt = false);
    /**
     * @brief sendRawData   发送原数据
     * @param audio
     * @param interrupt
     */
    void sendRawData(const std::string &raw, bool interrupt = false);
    void destroySession();
private:
    bool threadLoop();
public:
    bool  done{false};
    WebSocket::pointer ws{NULL};
    //void threadFun(string url, _ConnectionCallback cb, _HandlerMessageCallback hb);
    static unsigned int __stdcall WriteProc(void * paramptr) ;
  //  std::unique_ptr<std::thread> m_workThread;

    HANDLE  thread_hdl_;
    unsigned int  thread_id_;

    std::string sUrl;
    _ConnectionCallback __cb;
    _HandlerMessageCallback __hb;
    HANDLE mMutex;
};

#endif // MVS_H
