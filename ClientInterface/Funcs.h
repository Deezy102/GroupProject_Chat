#ifndef FUNCS_H
#define FUNCS_H

#include <QString>
#include "client.h"

QByteArray server_query(QString name, QString password, QString funcSwitch);
QByteArray server_query(QString login, QString chatName, QString msg,  QString funcSwitch);
QByteArray server_query(QString login, QString funcSwitch);
bool correctLogPass(QString login, QString pass, QString verpass);

#endif // FUNCS_H
