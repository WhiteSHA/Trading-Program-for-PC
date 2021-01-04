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

    bool getUserByUsername(User* user, QString username);

    bool addUserDepartment(int user_id, int dep_id);

    bool deleteUserDepartments(int user_id);

    bool getUserDepartments(Department* deps, int user_id);

    //  Departments API
    bool insertDepartment(Department* dep);

    bool updateDepartment(Department* dep);

    bool getDepartment(Department* dep, int dep_id);

    bool getDepartmentsCount(int& count);

    bool getLastDepartmentId(int& last_id);

    bool deleteDepartment(int dep_id);

    //  Measurement Units API
    bool getMeasurementUnits(MeasurementUnit* units, int& count);

    bool getMeasurementUnitsCount(int& count);

    bool getMeasurementUnit(MeasurementUnit* unit, int measUnitID);

    //  Products API
    bool insertProduct(Product* product);

    bool updateProduct(Product product);

    bool getProduct(Product* ptoduct, int prodID);

    bool getProductsCount(int& count);

    bool getLastProductId(int& lastID);

    bool deleteProduct(int prodID);

    bool deleteDepartmentProducts(int depID);

    bool deleteAllProducts();
};

#endif // DATABASE_H
