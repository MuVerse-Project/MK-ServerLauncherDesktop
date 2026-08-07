#include "WebSocketManager.hpp"

//我靠我终于把18码服务器删了

namespace CMS
{
    QUrl APIPOINT::buildUrl(const std::string_view path)
    {
        QUrl Tmp;
        Tmp.setScheme("ws");
        Tmp.setHost("127.0.0.1");
        Tmp.setPort(20038);
        Tmp.setPath(QString::fromUtf8(path.data(), static_cast<int>(path.size())));

        return std::move(Tmp);
    }


    WebSocketBase::WebSocketBase(
        QObject* parent,
        const int& Targetport,
        const std::shared_ptr<spdlog::logger>& ClientLogger):
        QObject(parent),
        client_(nullptr),
        Cur_WebSocketState_Client(WebSocketState_Client::Client_None),
        ClientLogger_(ClientLogger)
    {
        QString LoServerName = "CMS";

        client_ = new QWebSocket();
        client_->setParent(this);


        connect(client_, &QWebSocket::connected, this, &WebSocketBase::OnConnectedToServer);
        connect(client_, &QWebSocket::disconnected, this, &WebSocketBase::OnDisconnectedFromServer);
        connect(client_, &QWebSocket::textMessageReceived, this, &WebSocketBase::MessageFromServer);

    }
    WebSocketBase::~WebSocketBase(){if (client_) {client_->close();client_->deleteLater();client_ = nullptr;}}


    void WebSocketBase::OnConnectedToServer()
    {
        Cur_WebSocketState_Client = WebSocketState_Client::Client_Connected;
        ClientLogger_->info("=== Connected to server ===");
        ClientLogger_->info("Server URL: " + client_->requestUrl().toString().toStdString());
        ClientLogger_->info("Peer address: " + client_->peerAddress().toString().toStdString());
        ClientLogger_->info("Peer port: " + QString::number(client_->peerPort()).toStdString());
        ClientLogger_->info("Local address: " + client_->localAddress().toString().toStdString());
        ClientLogger_->info("Local port: " + QString::number(client_->localPort()).toStdString());


    }

    void WebSocketBase::OnDisconnectedFromServer() const
    {
        ClientLogger_->info("=== Disconnect From server ===");

    }

    void WebSocketBase::MessageFromServer(const QString& message) const
    {
        HandleMon(message.toStdString());

    }





}
