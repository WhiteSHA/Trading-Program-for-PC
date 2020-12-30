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

    // Standart Open
    bool open();

    // Standart Close
    bool close();

    // When DB is empty, then populate it with initial data
    bool populate();

private:

    //  Users API
    bool insertUser(User *user);

    bool updateUser(User* user);

    bool getUser (User* users, int user_id);

    bool getUsersCount(int* count);

};

#endif // DATABASE_H
