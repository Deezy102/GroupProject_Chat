#include "Funcs.h"

bool correctLogPass(QString login, QString pass, QString verpass)
{
    if (pass == verpass && !pass.isEmpty())
        return (checkText(login, "") && checkText(pass, "pass"));

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


bool checkText(QString str, QString fswitch)
{
    bool flag = true;

    vector<QString> forbidden = {"&", "_", " "};

    if (fswitch == "pass")
    {
        forbidden = {"&", "_"};
    }

    if (!str.isEmpty())
    {
        for (int i = 0; i < int(forbidden.size()); i++)
            flag *= !str.contains(forbidden[i]);

        return flag;
    }

    return false;
}

