#include "TcpClient.h"

#include <QCoreApplication>
#include <QTimer>
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    TcpClient client(12346);

    QTimer::singleShot(0, [&client](){
        client.startConnection();
    });
    QTimer::singleShot(1000, [&client](){
        client.sendsMessage("eeeee babe");
    });

    return app.exec();

    return EXIT_SUCCESS;
}
