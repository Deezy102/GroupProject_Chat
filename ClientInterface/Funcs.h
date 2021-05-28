#ifndef FUNCS_H
#define FUNCS_H

#include <QString>
#include "client.h"
#include <vector>

using std::vector;

QByteArray server_query(QString funcSwitch, QString first, QString second);
QByteArray server_query(QString funcSwitch, QString first, QString second, QString msg);
QByteArray server_query(QString funcSwitch, QString arg);

bool correctLogPass(QString login, QString pass, QString verpass);
bool checkText(QString logpass, QString fswitch);

#endif // FUNCS_H
