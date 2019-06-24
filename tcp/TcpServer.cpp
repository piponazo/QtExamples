#include "TcpServer.h"

#include <QTcpServer>
#include <QTcpSocket>

#include <iostream>

struct TcpServer::Pimpl : public QObject {
    TcpServer* parent;
    QTcpServer* tcpServer;
    QTcpSocket* clientConnection;

    Pimpl(quint16 port, TcpServer* parent_)
        : parent(parent_)
        , tcpServer(new QTcpServer(parent_))
        , clientConnection(nullptr)
    {
        if (!tcpServer->listen(QHostAddress::LocalHost, port)) {
            throw std::runtime_error("Unable to start the server: " + tcpServer->errorString().toStdString());
        }

        connect(tcpServer, &QTcpServer::newConnection, this, &TcpServer::Pimpl::newConnection);
    }

private slots:
    void newConnection()
    {
        clientConnection = tcpServer->nextPendingConnection();

        connect(clientConnection, &QAbstractSocket::disconnected, this, &Pimpl::disconnection);
        connect(clientConnection, &QAbstractSocket::readyRead, this, &Pimpl::commandReady);
        connect(clientConnection,
                QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
                this,
                &Pimpl::displayError);

        emit parent->connection();
    }

    void commandReady()
    {
        QString message(clientConnection->readAll());
        parent->processCommand(message);
        emit parent->commandReceived();
    }

    void disconnection()
    {
        clientConnection = nullptr;
        emit parent->disconnected();
    }

    void displayError(QAbstractSocket::SocketError socketError)
    {
        switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            std::cerr << "The host was not found. Please check the host name and port settings.\n";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            std::cerr << "The connection was refused by the peer. "
                         "Make sure the fortune server is running, "
                         "and check that the host name and port "
                         "settings are correct.\n";
            break;
        default:
            std::cerr << "The following error occurred: " << clientConnection->errorString().toStdString() << std::endl;
        }
    }
};

TcpServer::TcpServer(quint16 port, QObject* parent)
    : QObject(parent)
    , p_(new Pimpl(port, this))
{
}

TcpServer::~TcpServer() = default;
