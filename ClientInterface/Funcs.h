#ifndef FUNCS_H
#define FUNCS_H

#include <QString>
#include "client.h"

bool correctLogPass(QString login, QString pass, QString verpass);

QByteArray server_query(QString name, QString password, QString funcSwitch);

#endif // FUNCS_H
