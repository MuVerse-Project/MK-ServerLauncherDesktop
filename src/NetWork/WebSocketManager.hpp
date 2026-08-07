#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H
#include "../HolyHead.hpp"

namespace CMS
{








    struct APIPOINT
    {
        static constexpr const char* ENV_CREATE = "/api/v1/env/create";
        static constexpr const char* ENV_DELETE = "/api/v1/env/delete";
        static constexpr const char* ENV_LIST = "/api/v1/env/list";

        static constexpr const char* SERVER_AVAILABLE_TYPE = "/api/v1/server/availableType";
        static constexpr const char* SERVER_CREATE = "/api/v1/server/create";
        static constexpr const char* SERVER_DELETE = "/api/v1/server/delete";
        static constexpr const char* SERVER_FORCESTOP = "/api/v1/server/forcestop";
        static constexpr const char* SERVER_IMPORT = "/api/v1/server/import";
        static constexpr const char* SERVER_LIST = "/api/v1/server/list";
        static constexpr const char* SERVER_REMOVE = "/api/v1/server/remove";
        static constexpr const char* SERVER_START = "/api/v1/server/start";
        static constexpr const char* SERVER_STOP = "/api/v1/server/stop";

        static constexpr const char* OVERVIEW = "/api/v1/overview";
        static constexpr const char* MUCLOSE = "/muclose";

        static QUrl buildUrl(const std::string_view path);
    private:

    };



    class WebSocketBase : public QObject
    {
        Q_OBJECT
    public:
        explicit WebSocketBase(
            QObject* parent,
            const int& Targetport,
            const std::shared_ptr<spdlog::logger>& ClientLogger
        );
        ~WebSocketBase() override;


    signals:

    void systemStatusUpdated(int cpu, int mem, int totalServer,
                             int onlineServer, int offlineServer) const;

    protected slots:
        // Client slots
        virtual void OnConnectedToServer();
        //TODO 带参数重载
        virtual void OnDisconnectedFromServer() const;
        virtual void MessageFromServer(const QString& message) const;
    protected:
        void HandleMon(const std::string_view msg) const
        {
            nlohmann::json j = nlohmann::json::parse(msg);

            emit systemStatusUpdated(
                static_cast<int>(j["systemStatus"]["CpuUsage"].get<double>()),
                static_cast<int>(j["systemStatus"]["MemUsage"].get<double>()),
                j["serverStatus"]["totalServer"].get<int>(),
                j["serverStatus"]["onlineServer"].get<int>(),
                j["serverStatus"]["offlineServer"].get<int>()
                );
        }


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
