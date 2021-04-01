#include "functions.h"

map<string, string> read_from_file() {

    std::map<string, string> mp;
    ifstream file("D:\\chat\\db_test\\db.txt", std::ios::in);
    if (!file.is_open()) {
        qDebug() << "try again";
    }
    else {
        while (!file.eof()) {
            string name;
            string pass;
            file >> name;
            file >> pass;
            mp.insert(make_pair(name, pass));
        }

    }
    file.close();
    return mp;
}

bool write_to_file(map<string, string> &mp)
{
    map<string, string>::iterator iter;
    ofstream file;
    file.open("D:\\chat\\db_test\\db.txt", ofstream::out | ofstream::trunc);
    if (file.is_open() == true) {
        for (iter = mp.begin(); iter != mp.end(); iter++) {
            file << (*iter).first << " " << iter->second << std::endl;
        }
        file.close();
        return true;
    }
    else {

        return false;
    }

}


