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
};

#endif // DATABASE_H
