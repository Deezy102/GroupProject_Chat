#include "Funcs.h"

bool correctLogPass(QString login, QString pass, QString verpass)
{
    if (pass == verpass)
        return !(QString(login + pass).contains(" ") || QString(login + pass).contains("&"));

    return false;
}

QByteArray server_query(QString name, QString password, QString funcSwitch)
{
    QString message = funcSwitch+"&"+name+"&"+password;
    //qDebug() << message;
    QByteArray array;
    array.append(message);
    return array;
}
