#ifndef DB_H
#define DB_H
#include <sqlite3.h>

class DB {
public:
    sqlite3 *db;
    int rc;
    sqlite3_stmt *stmt;
    DB (const char*);
private:
    void init(const char*);
};

namespace user {
    void register_(DB*, const char*, const char*);
    void createTable(DB*);
}

#endif // DB_H
