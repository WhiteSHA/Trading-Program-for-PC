#ifndef DATABASE_H
#define DATABASE_H

#include "Utils/DataStructs.h"

class Database
{
public:
    Database();

    ~Database();

    // Public API`s (like Open, Close)
public:
    //  ***         GENERAL API         *** ///
    // Standart Open
    bool open();

    // Standart Close
    bool close();

    // When DB is empty, then populate it with initial data
    bool populate();

    //  **  // helpers
    bool containsData();

    bool dropTables();

    bool createTables();

    bool doStandartInserts();

public:

    //  Users API
    bool insertUser(User* user);

    bool updateUser(User* user);

    bool getUser(User* user, int user_id);

    bool getUsersCount(int& count);

    bool getLastUserId(int& last_id);

    bool deleteUser(int user_id);

};

#endif // DATABASE_H
