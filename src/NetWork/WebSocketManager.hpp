#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H
#include "../HolyHead.hpp"

namespace CMS
{
    class WebSocketBase : public QObject
    {
        Q_OBJECT
    public:
        explicit WebSocketBase(
            QObject* parent,
            const int& Targetport,
            const QString& path,
            const std::shared_ptr<spdlog::logger>& ClientLogger
        );
        ~WebSocketBase() override;
    protected slots:
        // Client slots
        virtual void OnConnectedToServer();
        //TODO 带参数重载
        virtual void OnDisconnectedFromServer() const;
        virtual void MessageFromServer(const QString& message) const;
    protected:
        //WebSocket.kt
        enum ApiWithArg
        {
            Server, //server/{msid} [WebSocket]
        };
        enum ApiWithOutArg
        {
            Overview,//Overview [WebSocket]
            Close//server/list [Get]
        };

        QWebSocket* client_;
        QUrl Muurl;
        enum WebSocketState_Client
        {
            Client_None, //默认
            Client_Disconnected, //已断开
            Client_Connecting, //连接中
            Client_Connected, //已连接
            Client_Reconnecting, //重连中
            Client_Error, //你报错了孩子!
            Client_Aborted //被强制中断
        };
        WebSocketState_Client Cur_WebSocketState_Client;
        std::shared_ptr<spdlog::logger> ClientLogger_;
    };





    class WebSocketEnv : public WebSocketBase
    {
        Q_OBJECT
    public:
        explicit WebSocketEnv(
            QObject* parent,
            const int& Targetport,
            const QString& path,
            const std::shared_ptr<spdlog::logger>& ClientLogger
        );
        ~WebSocketEnv() override;
    protected slots:
        // Client slots
        void OnConnectedToServer() override;
        void OnDisconnectedFromServer() const override;
        void MessageFromServer(const QString& message) const override;
    protected:
        //EnvRouter.kt
        enum ApiWithArg
        {
            Delete //env/delete/{name} [GET]
        };
        //EnvRouter.kt
        enum ApiWithOutArg
        {
            Create, //env/create [POST]
            List //env/list [GET]
        };

    };





    class WebSocketServer : public WebSocketBase
    {
        Q_OBJECT
    public:
        explicit WebSocketServer(
            QObject* parent,
            const int& Targetport,
            const QString& path,
            const std::shared_ptr<spdlog::logger>& ClientLogger
        );
        ~WebSocketServer() override;
    protected slots:
        // Client slots
        void OnConnectedToServer() override;
        void OnDisconnectedFromServer() const override;
        void MessageFromServer(const QString& message) const override;
    protected:
        //ServerRouter.kt
        enum ApiWithArg
        {
            Delete, //server/delete/{msid} [GET]
            Forcestop, //server/forcestop/{msid} [GET]
            Remove, //server/remove/{msid} [GET]
            Start, //server/start/{msid} [GET]
            Stop //server/stop/{msid} [GET]
        };
        enum ApiWithOutArg
        {
            Create,//server/create [POST]
            List//server/list [GET]
        };

    };
}

#endif //WEBSOCKETMANAGER_H
