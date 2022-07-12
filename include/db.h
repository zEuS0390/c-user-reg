#ifndef DB_H
#define DB_H
#include <sqlite3.h>
#include <string>

typedef unsigned int statust;

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
    statust register_(DB*, const char*, const char*);
    statust createTable(DB*);
    bool containsDigits(std::string);
}

#endif // DB_H
