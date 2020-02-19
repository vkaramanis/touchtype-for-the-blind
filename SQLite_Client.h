#pragma once
#ifndef SQLITE_CLIENT
#define SQLITE_CLIENT

#include "sqlite/sqlite3.h"

class SQLite_Client {
private:
    sqlite3_stmt* stmt = NULL;
    sqlite3* database;
    char* zErrMsg = 0;
    int rc = 0;

    static int callback(void* data, int argc, char** argv, char** azColName);

public:
    SQLite_Client();

    SQLite_Client(const char* db);

    ~SQLite_Client();

    bool getValue(const char* cmd);

    int setStatement(const char* stm);

    /*
        to do 
        function for insert, get value(s), get db look, callback, error handling
    */

};


#endif // !SQLITE_CLIENT
