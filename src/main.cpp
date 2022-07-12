#include <iostream>
#include <fstream>
#include <string>
#include "db.h"
#define DBFILE "dbname.txt"

// Main function
int main(int argc, char **argv) {
    // Declare limited entries variable for loop control
    int entries = 3;

    std::ifstream ifs(DBFILE);
    std::string dbname;
    std::getline(ifs, dbname);

    // Instantiate database connection
    DB *db = new DB(dbname.c_str());

    delete &dbname;
    delete &ifs;

    // Create a user table if not exist
    user::createTable(db);

    std::cout << "Insert " << entries << ((entries>1)? " entries:": " entry:") << std::endl;
    while (entries > 0) {
        std::string first_name, last_name;
        std::cout << "First Name: ";
        std::getline(std::cin, first_name);
        if (user::containsDigits(first_name)) {
            std::cout << "Invalid input!" << std::endl;
            break;
        }
        std::cout << "Last Name: ";
        std::getline(std::cin, last_name);
        if (user::containsDigits(last_name)) {
            std::cout << "Invalid input!" << std::endl;
            break;
        }
        statust status = user::register_(db, first_name.c_str(), last_name.c_str());
        delete &first_name;
        delete &last_name;
        entries--;
        if (status != 0) {
            break;
        }
    }

    std::cout << "Press enter to exit...";
    std::cin.get();
    return 0;
}
