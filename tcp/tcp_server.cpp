#include "TcpServer.h"

#include <QCoreApplication>
#include <iostream>

using namespace std;

class MyServer : public TcpServer
{
public:
    MyServer(quint16 port): TcpServer(port)
    {
    }
private:
    void processCommand(const QString &message)
    {
        cout << "MyServer: " << message.toStdString() << endl;
        if (message.startsWith("close"))
        {
            closeConnection();
        }
    }
};

int main (int argc, char **argv)
{
    cout << "Hello world!\n";
    QCoreApplication app(argc, argv);
    MyServer server(12346);

    QObject::connect(&server, &MyServer::disconnected, &app, &QCoreApplication::quit);

    return app.exec();
}
