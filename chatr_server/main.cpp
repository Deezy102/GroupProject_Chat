#include <QCoreApplication>
#include "tcpserver.h"
#include "database.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tcpServer server;
    database database;
    return a.exec();
}
