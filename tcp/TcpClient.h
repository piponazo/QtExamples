#pragma once

#include <QObject>

#include <memory>

/// Tcp client for localhost communications.
///
/// At the moment, a client can send messages with sendsMessage() but it does not get confirmations.
class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(quint16 port = 1234, QObject* parent = nullptr);
    ~TcpClient();

    void sendsMessage(const QString& msg);

signals:
    /// Indicates that the client connected successfully to a TCP server
    void connected();

    /// Indicates that the client could not connect a TCP server
    void connectionError();

public slots:
    /// Connects to a TCP server listening in \b port.
    void startConnection();

    /// Disconnect from the TCP server.
    void closeConnection();

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> p_;
};
