#include "Funcs.h"

bool correctLogPass(QString login, QString pass, QString verpass)
{
    if (pass == verpass && !pass.isEmpty())
        return checkText(login+pass);

    return false;
}

//bool clearlogin(QString logpass)
//{
//    qDebug() << logpass;

//}


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

QByteArray server_query(QString funcSwitch, QString arg)
{
    QString message = funcSwitch+"&"+arg;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}


bool checkText(QString str)
{
    vector<QString> forbidden = {"&", "_", " "};

    bool flag = true;

    int spaceCounter = 0;

    for (int i = 0; i < str.length(); i++)
        if  (str.contains(" "))
             spaceCounter++;

    if (str.length() != spaceCounter && !str.isEmpty())
    {
        for (int i = 0; i < int(forbidden.size()); i++)
            flag *= !(str).contains(forbidden[i]);

        return flag;
    }
    else
        return false;
}

