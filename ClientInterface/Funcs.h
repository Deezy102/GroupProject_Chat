/**
*  \file
*  \brief Заголовочный файл с описанием функций формирования сообщений
*  для сервера и проверки корректности ввода в текстовые поля
*/
#ifndef FUNCS_H
#define FUNCS_H

#include <QString>
#include "client.h"
#include <vector>
#include <qrsaencryption.h>

using std::vector;

QByteArray server_query(QString funcSwitch, QString first, QString second);
QByteArray server_query(QString funcSwitch, QString first, QString second, QString msg);
QByteArray server_query(QString funcSwitch, QString arg);

QByteArray encryption(QByteArray msg, QByteArray privcl, QByteArray pubcl, QByteArray servkey);

bool correctLogPass(QString login, QString pass, QString verpass);
bool checkText(QString logpass, QString fswitch);

#endif // FUNCS_H
