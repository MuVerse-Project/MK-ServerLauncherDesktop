#include "WebSocketManager.hpp"
#include <QMainWindow>
#include <QObject>

namespace CMS
{
    WebSocketManager::WebSocketManager(
        QObject* parent,
        const int& Targetport,
        const QString& Targetaddr,
        const int& Localport,
        const QString& path,
        const std::shared_ptr<spdlog::logger>& ServerLogger,
        const std::shared_ptr<spdlog::logger>& ClientLogger)

        :
        QObject(parent),
        client_MuCloud(nullptr),
        client_(nullptr),
        server_(nullptr),
        Cur_WebSocketState_Client(WebSocketState_Client::Client_None),
        Cur_WebSocketState_Server(WebSocketState_Server::Server_NotListening),
        ServerLogger_(ServerLogger),
        ClientLogger_(ClientLogger)

    {
        Muurl.setScheme("wss");
        Muurl.setHost("localhost");
        Muurl.setPort(Targetport);
        Muurl.setPath(path);
        QString LoServerName = "CMS";


        server_ = new QWebSocketServer(LoServerName, QWebSocketServer::NonSecureMode, this);
        client_ = new QWebSocket();
        client_->setParent(this);

        //QUrl test = QUrl("wss://echo.websocket.org");
        if (!Muurl.isValid())
        {
            ClientLogger_->error("Invalid URL: {}", Muurl.toString().toStdString());
            Cur_WebSocketState_Client = WebSocketState_Client::Client_Error;

            //TODO(Hzj) : 错误处理重连
            //while (true){}


            return;
        }
        else
        {
            ClientLogger_->info("Valid URL: {}", Muurl.toString().toStdString());
            client_->open(Muurl);
            Cur_WebSocketState_Client = WebSocketState_Client::Client_Connecting;
            ClientLogger_->info("Connecting to {}", Muurl.toString().toStdString());
        }


        if (!server_->listen(QHostAddress::Any, 4030))
        {
            ServerLogger_->error("Failed to start WebSocket server on port 4030: {}",
                                 server_->errorString().toStdString());
        }
        else
        {
            ServerLogger_->info("WebSocket server started successfully on port 4030");
            Cur_WebSocketState_Server = WebSocketState_Server::Server_Listening;
            connect(server_, &QWebSocketServer::newConnection, this, &WebSocketManager::OnClientConnectedToServer);
        }


        connect(client_, &QWebSocket::connected, this, &WebSocketManager::OnConnectedToServer);
        connect(client_, &QWebSocket::disconnected, this, &WebSocketManager::OnDisconnectedFromServer);
        connect(client_, &QWebSocket::textMessageReceived, this, &WebSocketManager::MessageFromServer);
    }

    void WebSocketManager::OnConnectedToServer()
    {
        Cur_WebSocketState_Client = WebSocketState_Client::Client_Connected;
        ClientLogger_->info("=== Connected to server ===");
        ClientLogger_->info("Server URL:" + client_->requestUrl().toString().toStdString());
        ClientLogger_->info("Peer address:" + client_->peerAddress().toString().toStdString());
        ClientLogger_->info("Peer port:" + QString::number(client_->peerPort()).toStdString());
        ClientLogger_->info("Local address:" + client_->localAddress().toString().toStdString());
        ClientLogger_->info("Local port:" + QString::number(client_->localPort()).toStdString());

        client_->sendTextMessage("Hello MuCloud!");
    }

    void WebSocketManager::OnDisconnectedFromServer() const
    {
        ClientLogger_->info("=== Disconnect to server ===");

    }

    void WebSocketManager::MessageFromServer(const QString& message) const
    {
        ClientLogger_->info("=== Message From Server ===");
        ClientLogger_->info("{}", message.toStdString());

    }

    void WebSocketManager::MessageFromClient(const QString& message) const
    {
        QWebSocket* client = qobject_cast<QWebSocket*>(sender());
        ServerLogger_->info("=== Message From Client ===");
        ServerLogger_->info("{}", message.toStdString());

        client->sendTextMessage(message);
    }


    void WebSocketManager::OnClientConnectedToServer()
    {
        if (client_MuCloud)
        {
            QWebSocket* extra = server_->nextPendingConnection();
            extra->sendTextMessage("Server already has a client, connection rejected");

            // TODO(Hzj) : hey JUST Let Him CLOSE!!!

            extra->close();

            return;
        }

        client_MuCloud = server_->nextPendingConnection();
        client_MuCloud->setParent(this);
        Cur_WebSocketState_Server = WebSocketState_Server::Server_ClientConnected;

        ServerLogger_->info("=== MuCloud Connected ===");
        ServerLogger_->info("MuCloud address: {}", client_MuCloud->peerAddress().toString().toStdString());
        ServerLogger_->info("MuCloud port: {}", client_MuCloud->peerPort());

        connect(client_MuCloud, &QWebSocket::textMessageReceived, this, &WebSocketManager::MessageFromClient);
        connect(client_MuCloud, &QWebSocket::disconnected, this, [this]()
        {
            ServerLogger_->info("MuCloud disconnected");


            if (client_MuCloud)
            {
                client_MuCloud->deleteLater();
                client_MuCloud = nullptr;
            }

            Cur_WebSocketState_Server = WebSocketState_Server::Server_NotListening;
        });
    }
}
