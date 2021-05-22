#include "Funcs.h"

bool correctLogPass(QString login, QString pass, QString verpass)
{
    if (pass == verpass)
        return clearlogin(login+pass);

    return false;
}

bool clearlogin(QString logpass)
{
    qDebug() << logpass;
    vector<QString> forbidden = {"&", "_", " ", ""};

    bool flag = true;

    for (int i = 0; i < int(forbidden.size()); i++)
        flag *= !logpass.contains(forbidden[i]);

    qDebug() << flag;
    return flag;
}


QByteArray server_query(QString funcSwitch, QString first, QString second)
{
    QString message = funcSwitch+"&"+first+"&"+second;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}

QByteArray server_query(QString funcSwitch, QString first, QString second, QString msg)
{
    QString message = funcSwitch+"&"+first+"&"+second+"&"+msg;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}

