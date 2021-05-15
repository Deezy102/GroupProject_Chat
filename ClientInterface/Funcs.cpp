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
    vector<QString> forbidden = {"&", "_", " "};

    bool flag = true;

    for (int i = 0; i < int(forbidden.size()); i++)
    {

        flag *= !logpass.contains(forbidden[i]);

    }
    qDebug() << flag;
    return flag;
}


QByteArray server_query(QString name, QString password, QString funcSwitch)
{
    QString message = funcSwitch+"&"+name+"&"+password;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}

QByteArray server_query(QString login, QString chatName, QString msg,  QString funcSwitch)
{
    QString message = funcSwitch+"&"+login+"&"+chatName+"&"+msg;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}

