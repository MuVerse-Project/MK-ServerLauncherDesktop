#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H
#include "spdlog/spdlog.h"
#include <QMainWindow>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>
#include <QObject>
#include <memory>

namespace CMS
{
    class WebSocketManager : public QObject
    {
        Q_OBJECT

    public:
        explicit WebSocketManager(
            QObject* parent,
            const int& Targetport,
            const QString& Targetaddr,
            const int& Localport,
            const QString& path,
            const std::shared_ptr<spdlog::logger>& ServerLogger,
            const std::shared_ptr<spdlog::logger>& ClientLogger
        );

        //~WebSocketManager();

    private slots:
        // Client slots
        void OnConnectedToServer();
        void OnDisconnectedFromServer() const;
        void MessageFromServer(const QString& message) const;

        //其实你们要知道的,MuCloud的Websocket的所有信号属于服务器的槽,至少现在是这样
        // Server slots
        //void OnServerStopped();
        void OnClientConnectedToServer();
        void MessageFromClient(const QString& message) const;
        //void OnclientDisconnected(const QString& clientId);
        //void MessageFromClient(const QString& clientId, const QString& message);


    private:
        QWebSocket* client_MuCloud;
        QWebSocket* client_;
        QWebSocketServer* server_;
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

        enum WebSocketState_Server
        {
            Server_NotListening, //默认
            Server_Listening, //监听
            Server_Closing, //关闭
            Server_ClientConnected, //已连接
            Server_Error //你报错了孩子!
        };

        WebSocketState_Server Cur_WebSocketState_Server;

        std::shared_ptr<spdlog::logger> ServerLogger_;
        std::shared_ptr<spdlog::logger> ClientLogger_;
    };
}

#endif //WEBSOCKETMANAGER_H
