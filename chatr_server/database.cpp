/**
*  \file
*  \brief Файл с реализацией функций работы с БД и хранилищем переписок
*/
#include "database.h"

bool flag = true;
const string path = "D:\\Chat_project\\GroupProject_Chat\\chatStorage\\";
QByteArray read_from_file(string chatName, int serialNum)
{
    //сериалНум - порядковый номер сообщения которое необходимо вывести
    //для слотСерверВрайтМесседж значение вшито в код и равно 0(новейшее сообщение переписки)
    //для слотЛодЧатРум задается итератором из заданного множителем диапазона(первая подгрузка переписки и просмотр старых сообщений)
    string str;
    ifstream file(path + chatName + ".txt", std::ios::in);
    if (!file.is_open())
    {
        qDebug() << "try again";
    }
    else
    {
        string buf;
        int counter = 0;
        //цикл переводит курсор на нужную строку
        while (!file.eof() && counter < serialNum)
        {
            std::getline(file, buf);
            counter++;
            buf = "";
        }
        //считываем нужное сообщение
        std::getline(file, buf);
        str = buf;//подумал, что надо добавить какой-то флаг для вычленения сообщения на клиенте
        qDebug() << "strReadFromFile:::" + QByteArray::fromStdString(str);
    }

    file.close();
    //добавить проверку на пустоту строки, чтобы не забивать модели пустыми сообщениями
    return QByteArray::fromStdString(str);
}
/**
 * @brief write_to_file отвечает за запись сообщения в соответствующий файл переписки
 * @param login - переменная, отвечающая за имя пользователя
 * @param chatName - переменная, отвечающая за название переписки, в которую будет произведена запись
 * @param msg - переменная, отвечающая за сообщение, которое будет записано в файл
 * @return возвращает булево значение об успехе выполнения функции
 *
 * Краткое описание работы:
 *
 * Функция получает на вход три параметра: логин, имя чата, сообщение.
 *
 * Далее по полученному названию чата открывается, соответствующий файл переписки
 * (если его нет, то создается и функция вызывается еще раз).
 *
 * После чего создается новый файл, в который записывается новое сообщение с добавлением даты и именем отправителя.
 *
 * Затем данные из старого файла переписываются в новый файл.
 *
 * Старый файл удаляется.
 *
 * Новый файл изменяет название на имя старого файла.
 *
 * Возращается булево значение о выполнении функции.
 */
bool write_to_file(string login, string chatName, string msg)
{
    ifstream oldFile;
    oldFile.open(path + chatName + ".txt", ifstream::in);

    if (oldFile.is_open() == true)
    {
        ofstream newFile;
        newFile.open(path + chatName + "_temp.txt", ofstream::out | ofstream::app | ofstream::ate);

        if (newFile.is_open())
        {
            QString time_format = "dd-MM-yy  HH:mm";
            QDateTime qdate = QDateTime::currentDateTime();
            QString sdate = qdate.toString(time_format);

            newFile << "(" << sdate.QString::toStdString() << ")" << login << ": " << msg << std::endl;

            string buf;
            while (getline(oldFile, buf))
                newFile << buf << std::endl;
        }

        oldFile.close();
        newFile.close();

        string oldPath = path + chatName + ".txt";
        string newPath = path + chatName + "_temp.txt";
        const char *oldChar = oldPath.c_str();
        const char *newChar = newPath.c_str();

        remove(oldChar);
        rename(newChar, oldChar);

        return true;
    }
    else
    {
        ofstream createFile;
        createFile.open(path + chatName + ".txt", ofstream::out);
        createFile.close();
        write_to_file(login, chatName, msg);
    }
    return true;
}
/**
 * @brief init_db отвечает за подключение и открытие базы данных PostgreSQL
 * @return возвращается объект базы данных
 *
 * Функция имеет флаг. Если он равен true, то создается новое подключение и открытие базы данных.
 * Если же он равен false, то происходит подключение к уже существующему соединению.
 */
QSqlDatabase init_db()
{
    QSqlDatabase db;
    if (flag)
    {
        db = QSqlDatabase::addDatabase("QPSQL", "db_connect");
        db.setHostName("localhost");
        db.setDatabaseName("chat");
        db.setUserName("postgres");
        db.setPassword("    ");
        flag = false;
    }
    else
        db = QSqlDatabase::database("db_connect");
    if (db.open())
        qDebug() << "db has opened";
    else
        qDebug() << "db has not opened" <<  db.lastError().text();
    return db;
}
/**
 * @brief registration отвечает за регистрацию нового пользователя в базе данных
 * @param logpass - это строка, содержащая логин и пароль будущего пользователя
 * @return возвращается сообщение об успешной или неуспешной регистрации пользователя
 *
 * Описание работы:
 *
 * Функция делит строку, полученную на вход, на логин и пароль.
 *
 * После этого создает подключение к базе данных и формирует SQL-запрос к ней на наличие такого логина в таблице пользователей.
 *
 * Если ответ запроса равен нулю строк (т.е. нет пользователей с таким логином), то формируется новый SQL-запрос на включение
 * пользователя с данной парой логин-пароль в таблицу пользователей, закрывает соединение с БД и
 * возвращается сообщение об успешной регистрации.
 *
 * В противном случае, закрывается соединение с БД и возвращается сообщение о неуспешной регистрации.
 *
 */
QByteArray registration(string logpass)
{
    QString login = QString::fromStdString(logpass.substr(0,logpass.find("&")));
    QString password = QString::fromStdString(logpass.substr(logpass.rfind("&") + 1, logpass.length()));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare("select * from users where login like :name");
    qr.bindValue(":name", login);
    qr.exec();

    if (qr.size()==0)
    {
        qr.prepare(QString("insert into users (login, password) values ('%1', '%2')").arg(login,password));
        qr.exec();

        db.close();

        return "successful registration";
    }

    db.close();

    return "choose antoher login";
}
/**
 * @brief authorization отвечает за авторизацию пользователя
 * @param logpass - это строка, содержащая логин, пароль и сокет существующего пользователя
 * @return сообщение об успешной или неуспешной авторизации
 *
 * Описание работы:
 *
 * Функция делит полученную строку на логин, пароль и номер сокета.
 *
 * Создает подключение к БД и формирует запрос на существование записи о пользователе в таблице.
 *
 * Если запись с данной парой логин-пароль существует, то формируется новый запрос на внесение изменения в запись
 * данного пользователя. Данный запрос добавляет информацию о текущем сокете пользователя. Возвращает
 * сообщение об успешной авторизации.
 *
 * Если запись с данной парой логин-пароль не нашлась возвращается сообщение об ошибке пользователя.
 *
 */
QByteArray authorization(string logpass)
{
    QString login = QString::fromStdString(logpass.substr(0,logpass.find("&")));
    QString password = QString::fromStdString(logpass.substr(logpass.find("&") + 1, logpass.rfind("&") - logpass.find("&") - 1));
    QString socket = QString::fromStdString(logpass.substr(logpass.rfind("&") + 1, logpass.length()));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    qr.prepare(QString("select count(*) from users where login like '%1' and password like '%2'").arg(login,password));
    qr.exec();
    qr.next();

    if (qr.value(0).toInt() == 1)
    {
        qr.prepare(QString("update users set current_socket = '%1' where login like '%2';").arg(socket,login));
        qr.exec();
        db.close();
        return "successful login";
    }

    db.close();
    return "invalid login or password";
}
/**
 * @brief message отвечает за вызов функции записи в файл и слота для отправки сообщения пользователям.
 * @param msgData - переменная, содержащая информацию об отправителе, названии переписки и самого сообщения.
 * @return возвращает флаг и название измененной переписки для последующего парсинга
 */
QByteArray message(string msgData)
{
    string login = msgData.substr(0,msgData.find("&"));
    msgData.erase(0,login.size() + 1);
    string chatName = msgData.substr(0, msgData.find("&"));
    msgData.erase(0,chatName.size() + 1);
    string msg = msgData;
    write_to_file(login, chatName, msg);

    return QByteArray::fromStdString("msg&" + chatName);
}
/**
 * @brief BDSocketClear отвечает за очистку столбца current_socket в таблице users.
 * @param socket_id - номер сокета, который нужно удалить.
 */
void BDSocketClear(int socket_id)
{
    QSqlDatabase db = init_db();
    QSqlQuery qr = QSqlQuery(db);

    qr.prepare(QString("update users set current_socket = null where current_socket = %1;").arg(socket_id));
    qr.exec();

    db.close();
}
/**
 * @brief loginToSocket отвечает за получением номера сокета по имеющемуся логину.
 * @param login - имя пользователя.
 * @return возвращает номер сокета.
 */
int loginToSocket(std::string login)
{
    QSqlDatabase db = init_db();
    QSqlQuery qr = QSqlQuery(db);

    qr.prepare(QString("select current_socket from users where login like '%1'").arg(QString::fromStdString(login)));
    qr.exec();
    qr.next();

    int rtrn = -1;
    rtrn = qr.value(0).toInt();

    db.close();
    return rtrn;
}
/**
 * @brief oldSocketsClear очищает весь столбец current_socket
 */
void oldSocketsClear()
{
    QSqlDatabase db = init_db();
    QSqlQuery qr = QSqlQuery(db);

    qr.prepare("update users set current_socket = null where current_socket > -1;");
    qr.exec();

    db.close();
}
/**
 * @brief chatCreation отвечает за создание нового чата.
 * @param chatData - строка, содержащая название чата, имя первого и второго пользователя.
 * @return сообщение об успешном или неудачном создании чата
 *
 * Описание работы:
 *
 * Функция делит полученную строка на название чата, логин первого пользователя и логин второго.
 *
 * Создает подключение к БД и формирует запрос на проверку существования собеседника и чата с таким названием.
 *
 * Если проверка пройдена, то в таблицу чатов добавляется запись о новом чате, закрывается соединение с БД и возвращается
 * сообщение об успешном создании.
 *
 * Если проверка не прошла, то закрывается соединение с БД и возвращается сообщение о неудачном создании чата.
 *
 */
QByteArray chatCreation(std::string chatData)
{
    QString chatName = QString::fromStdString(chatData.substr(0, chatData.find("&")));
    chatData.erase(0,chatName.size() + 1);
    QString contact1 = QString::fromStdString(chatData.substr(0, chatData.find("&")));
    chatData.erase(0, chatData.find("&") + 1);
    QString contact2 = QString::fromStdString(chatData);

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    QString buf = "select count(*) from users where login like '%1' and (select count(*) from chatlist where chatname = '%2') = 0;";
    qr.prepare(buf.arg(contact2, chatName));
    qr.exec();
    qr.next();

    if (qr.value(0).toInt() == 1 && contact1 != contact2)
    {
        qr.prepare(QString("insert into chatlist (chatname, userlist) values ('%1', '{%2, %3}')").arg(chatName, contact1, contact2));
        qr.exec();
        db.close();

        return "successful chat creation";
    }

    db.close();

    return "bad name of chat or login";
}
/**
 * @brief chatUserAdd отвечает за добавление пользователя в существующий чат.
 * @param msgData - строка, содержащая название чата и логин добавляемого пользователя.
 * @return возвращает сообщение об успешном или неудачном добавлении пользователя
 *
 * Описание работы:
 *
 * Функция делит полученную строку на название чата и логин добавляемого пользователя.
 *
 * Создается подключение к БД и формируется SQL-запрос для проверки.
 *
 * Если проверка прошла успешно, то пользователь добавляется в массив участников для соответствующего чата, закрывается соединение
 * с БД и возвращается сообщение об успешном добавлении.
 *
 * Если проверка не пройдена, то закрывается соединение с БД и возвращается сообщение о неудачном добавлении.
 */
QByteArray chatUserAdd(std::string msgData)
{
    QString chatName = QString::fromStdString(msgData.substr(0, msgData.find("&")));
    msgData.erase(0,chatName.size() + 1);
    QString userLogin = QString::fromStdString(msgData.substr(0, msgData.find("&")));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    QString buf = "select count(*) from chatlist where chatname = '%1' "
            "and not('%2' = ANY(userlist)) and (select count(*) from users where login like '%2') = 1;";
    qr.prepare(buf.arg(chatName, userLogin));
    qr.exec();
    qr.next();

    if (qr.value(0).toInt() == 1)
    {
        qr.prepare(QString("update chatlist set userlist = userlist || '{%1}' where chatname like '%2'").arg(userLogin, chatName));
        qr.exec();

        db.close();

        return "successful user addition";
    }

    db.close();

    return "fail user addition";
}

/**
 * @brief chatUserDel отвечает за удаление пользователя из существующего чата.
 * @param msgData - строка, содержащая имя чата, логин пользователя на удаление из чата.
 * @return сообщение об успешном удалении.
 */
QByteArray chatUserDel(std::string msgData)
{
    QString chatName = QString::fromStdString(msgData.substr(0, msgData.find("&")));
    msgData.erase(0,chatName.size() + 1);
    QString userLogin = QString::fromStdString(msgData.substr(0, msgData.find("&")));

    QSqlDatabase db = init_db();

    QSqlQuery qr = QSqlQuery(db);
    QString buf = "update chatlist set userlist = array_remove_item((select userlist from chatlist where chatname like '%1'), '%2')where chatname like '%1';";
    qr.prepare(buf.arg(chatName, userLogin));
    qr.exec();

    return "user deleted";
}
/**
 * @brief getChatlist формирует список доступных чатов.
 * @param login - имя пользователя.
 * @return вектор названий чатов.
 */
vector<string> getChatlist(string login){

    vector<string> list;

    QSqlDatabase db = init_db();
    QSqlQuery qr = QSqlQuery(db);
    //запос к бд на вывод всех чатов по логину
    qr.prepare("select chatname from chatlist where array_length(array_positions(userlist, :logname), 1) > 0;");
    qr.bindValue(":logname", QString::fromStdString(login));
    qr.exec();
    //добавляем названия чата в вектор стрингов
    while(qr.next())
        list.push_back(qr.value(0).toString().toStdString());

    db.close();

    return list;
}

