#include <iostream>
#include <algorithm>
#include <string>
#include "db.h"

DB::DB (const char* name)
{
        init(name);
}

// Initialize database connection
void DB::init(const char *name)
{
        rc = sqlite3_open(name, &db);
        // Check if result code of the connection is successful
        if (rc != SQLITE_OK)
        {
                std::cerr << "Error database connection" << std::endl;
        }
}

// Register a user with first_name and last_name
statust user::register_(DB* db, const char *first_name, const char *last_name)
{
        const char *query = "INSERT INTO user (first_name, last_name) VALUES (?, ?);";
        // Prepare the query statement
        db->rc = sqlite3_prepare_v2(db->db, query, -1, &db->stmt, NULL);
        if (db->rc != SQLITE_OK)
        {
                std::cerr << "Error preparing the query statement: " << sqlite3_errmsg(db->db) << std::endl;
                return 1;
        }
        sqlite3_bind_text(db->stmt, 1, first_name, -1, SQLITE_STATIC);
        sqlite3_bind_text(db->stmt, 2, last_name, -1, SQLITE_STATIC);
        db->rc = sqlite3_step(db->stmt);
        if (db->rc != SQLITE_DONE)
        {
                std::cerr << "Error executing the query: " << sqlite3_errmsg(db->db) << std::endl;
                return 2;
        }
        sqlite3_clear_bindings(db->stmt);
        sqlite3_reset(db->stmt);
        std::cout << "Successfully added '" << first_name << " " << last_name << "' in the database." << std::endl;
        return 0;
}

// Create a user table
statust user::createTable(DB* db)
{
        const char *query = "CREATE TABLE user (id integer primary key, first_name text not null, last_name text not null);";
        db->rc = sqlite3_prepare_v2(db->db, query, -1, &db->stmt, NULL);
        if (db->rc != SQLITE_OK)
        {
                std::cerr << "Error preparing the query statement: " << sqlite3_errmsg(db->db) << std::endl;
                return 1;
        }
        db->rc = sqlite3_step(db->stmt);
        if (db->rc != SQLITE_DONE)
        {
                std::cerr << "Error executing the query: " << sqlite3_errmsg(db->db) << std::endl;
                return 2;
        }
        else
        {
                std::cout << "Successfully created 'user' table." << std::endl;
        }
        sqlite3_reset(db->stmt);
        return 0;
}

bool user::containsDigits(std::string str)
{
        return std::any_of(str.begin(), str.end(), [](char c)->bool{return isdigit(c);});;
}
