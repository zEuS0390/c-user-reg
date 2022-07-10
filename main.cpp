#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sqlite3.h>
#define max_string_length 256

// Register User with first_name and last_name
void registerUser(
        sqlite3 **db,
        sqlite3_stmt **stmt,
        int &rc,
        const char *first_name,
        const char *last_name) {
    const char *query = "INSERT INTO user (first_name, last_name) VALUES (?, ?);";

    // Prepare the query statement
    rc = sqlite3_prepare_v2(*db, query, -1, stmt, NULL);

    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing the query statement: " << sqlite3_errmsg(*db) << std::endl;
        return;
    }

    sqlite3_bind_text(*stmt, 1, first_name, -1, SQLITE_STATIC);
    sqlite3_bind_text(*stmt, 2, last_name, -1, SQLITE_STATIC);

    rc = sqlite3_step(*stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing the query: " << sqlite3_errmsg(*db) << std::endl;
        return;
    }
    sqlite3_clear_bindings(*stmt);
    sqlite3_reset(*stmt);
    std::cout << "Successfully added '" << first_name << " " << last_name << "' in the database." << std::endl;
}

void createUserTable(
        sqlite3 **db,
        sqlite3_stmt **stmt,
        int &rc) {
    const char *query = "CREATE TABLE IF NOT EXISTS user (id integer primary key, first_name text not null, last_name text not null);";
    rc = sqlite3_prepare_v2(*db, query, -1, stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing the query statement: " << sqlite3_errmsg(*db) << std::endl;
        return;
    }
    rc = sqlite3_step(*stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing the query: " << sqlite3_errmsg(*db) << std::endl;
        return;
    }
    sqlite3_reset(*stmt);
    std::cout << "Successfully created 'user' table." << std::endl;
}

// Main function
int main(int argc, char **argv) {

    // initialize database
    sqlite3 *db;

    // rc means result code
    int rc;

    // open database connection
    rc = sqlite3_open("regusers.db", &db);

    // create a sql statement
    sqlite3_stmt *stmt;

    const char *sql;

    // Check if result code of the connection is successful
    if (rc != SQLITE_OK) {
        std::cerr << "Error database connection" << std::endl;
        return 1;
    }

    createUserTable(&db,&stmt,rc);

    while (true) {
        char *first_name = (char*)malloc(max_string_length);
        char *last_name = (char*)malloc(max_string_length);
        std::cout << "First Name: ";
        fgets(first_name, max_string_length, stdin);
        std::cout << "Last Name: ";
        fgets(last_name, max_string_length, stdin);
        first_name[strlen(first_name)-1] = '\0';
        last_name[strlen(last_name)-1] = '\0';
        registerUser(&db,&stmt,rc,first_name,last_name);
        free(first_name);
        free(last_name);
        first_name = NULL;
        last_name = NULL;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::cin.get();
    return 0;
}
