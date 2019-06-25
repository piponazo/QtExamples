#pragma once

#include <QObject>

#include <memory>

/// Tcp server for localhost communications
///
/// At the moment, the server just receives commands and it does not send any confirmation message to the clients.
///
/// Note that this is a base class. Child classes must implement the processCommand() method.
class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(quint16 port = 1234, QObject* parent = nullptr);
    ~TcpServer();

signals:
    /// Indicates that a connection with a client has been established.
    void connection();
    /// Indicates that the client has been disconnected.
    void disconnected();
    /// Indicates that a command has been received from the client.
    void commandReceived();

protected:
    void closeConnection();

private:
    /// Virtual m
    virtual void processCommand(const QString& message) = 0;

    struct Pimpl;
    std::unique_ptr<Pimpl> p_;
};
