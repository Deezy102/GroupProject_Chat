#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <string>
#include <map>
#include <QDebug>
#include <fstream>
#include <QTcpSocket>
#include "database.h"
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

using std::map;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::string;


map<string, string> read_from_file();
bool write_to_file(map<string, string> &mp);


#endif // FUNCTIONS_H
