#include "SQLite_Client.h"

SQLite_Client::SQLite_Client() {}

SQLite_Client::SQLite_Client(const char* db) {
    rc = sqlite3_open(db, &database);
}

SQLite_Client::~SQLite_Client() {
    sqlite3_close(database);
}

int SQLite_Client::callback(void* data, int argc, char** argv, char** azColName) {
    //to do
    return 0;
}

bool SQLite_Client::getValue(const char* cmd) {
    rc = sqlite3_prepare_v2(database, cmd, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {}

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) { return false; }
    else { return true; }
    sqlite3_finalize(stmt);
}

int SQLite_Client::setStatement(const char* stm) {
    return sqlite3_exec(database, stm, callback, 0, &zErrMsg);
}