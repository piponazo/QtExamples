#include "TcpServer.h"

#include <QCoreApplication>
#include <iostream>

using namespace std;

class MyServer : TcpServer
{
public:
    MyServer(quint16 port): TcpServer(port)
    {
    }
private:
    void processCommand(const QString &message)
    {
        cout << "MyServer: " << message.toStdString() << endl;
    }
};

int main (int argc, char **argv)
{
    cout << "Hello world!\n";
    QCoreApplication app(argc, argv);

    MyServer server(12346);
    return app.exec();
}
