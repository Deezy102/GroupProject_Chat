/**
* \file
* \brief Данный файл отвечает за реализацию main'а сервера
*
*/
#include <QCoreApplication>
#include "tcpserver.h"
#include "database.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tcpServer server;

    return a.exec();
}
