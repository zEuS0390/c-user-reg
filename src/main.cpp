#include <iostream>
#include <string>
#include "db.h"

// Main function
int main()
{
        // Declare limited entries variable for loop control
        int entries = 3;

        const std::string dbname = "database.db";

        // Instantiate database connection
        DB *db = new DB(dbname.c_str());

        // Create a user table if not exist
        user::createTable(db);

        std::cout << "Insert " << entries << ((entries>1)? " entries:": " entry:") << std::endl;

        while (entries > 0)
        {
                std::string first_name, last_name;
                std::cout << "First Name: ";
                std::getline(std::cin, first_name);
                if (user::containsDigits(first_name) || first_name.empty())
                {
                        std::cout << "Invalid input!" << std::endl;
                        break;
                }
                std::cout << "Last Name: ";
                std::getline(std::cin, last_name);
                if (user::containsDigits(last_name) || last_name.empty())
                {
                        std::cout << "Invalid input!" << std::endl;
                        break;
                }
                statust status = user::register_(db, first_name.c_str(), last_name.c_str());
                entries--;
                if (status != 0)
                {
                        break;
                }
        }

        delete db;
        db = nullptr;

        std::cout << "Press enter to exit...";
        std::cin.get();

        return 0;
}
