/**
*  \file
*  \brief Файл с реализацией функций формирования сообщений серверу и проверки текстовых полей.
*/
#include "Funcs.h"
/**
 * @brief correctLogPass проверка логина и пароля при регистрации
 * @param login - логин пользователя
 * @param pass - пароль пользователя
 * @param verpass - подтверждение пароля
 * @return
 */
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

/**
 * @brief server_query формирует сообщение для сервера
 * @param funcSwitch - флаг для парсинга на сервере
 * @param first - первый аргумент
 * @param second - второй аргумент
 * @return возвращает QByteArray с готовым для отправки сообщением
 */
QByteArray server_query(QString funcSwitch, QString first, QString second)
{
    QString message = funcSwitch+"&"+first+"&"+second;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}
/**
 * @brief server_query формирует сообщение для сервера
 * @param funcSwitch - флаг для парсинга на сервере
 * @param first - первый аргумент
 * @param second - второй аргумент
 * @param msg - сообщение пользователя
 * @return возвращает QByteArray с готовым для отправки сообщением
 */
QByteArray server_query(QString funcSwitch, QString first, QString second, QString msg)
{
    QString message = funcSwitch+"&"+first+"&"+second+"&"+msg;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}
/**
 * @brief server_query формирует сообщение для сервера
 * @param funcSwitch - флаг для парсинга на сервере
 * @param arg - аргумент
 * @return возвращает QByteArray с готовым для отправки сообщением
 */
QByteArray server_query(QString funcSwitch, QString arg)
{
    QString message = funcSwitch+"&"+arg;
    QByteArray array;
    array.append(message.toUtf8());
    return array;
}

/**
 * @brief checkText проверяет корректность введеной информации в текстовые поля
 * @param str - информация из текстового поля
 * @param fswitch - флаг для парсинга
 * @return булевое значение, соответствующее успешности выполнения функции.
 */
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

