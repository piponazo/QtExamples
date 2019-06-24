#include "TcpClient.h"

#include <QHostInfo>
#include <QTcpSocket>

struct TcpClient::Pimpl : public QObject {
    Pimpl(quint16 port_, TcpClient* parent)
        : tcpSocket(new QTcpSocket(parent))
        , port(port_)
    {
        connect(tcpSocket, &QTcpSocket::connected, parent, &TcpClient::connected);
        connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                parent, SIGNAL(connectionError()));
    }

    QTcpSocket* tcpSocket;
    quint16 port;
};

TcpClient::TcpClient(quint16 port, QObject* parent)
    : QObject(parent)
    , p_(new Pimpl(port, this))
{
}

TcpClient::~TcpClient() {}

void TcpClient::startConnection()
{
    p_->tcpSocket->connectToHost(QHostAddress::LocalHost, p_->port);
}

void TcpClient::closeConnection()
{
    p_->tcpSocket->close();
}

void TcpClient::sendsMessage(const QString& msg)
{
    p_->tcpSocket->write(msg.toLocal8Bit());
//    BlockWriter(p_->tcpSocket).stream() << msg;
}
