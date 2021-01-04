#include "Database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "CoreGlobals.h"
#include "Utils/StandardQueries.h"

#include <QDebug>

Database::Database()
{

}

Database::~Database()
{
    close();
}

bool Database::open()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("shop.db");

    if (!database.open())
        return false;
    return true;
}

bool Database::close()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("shop.db");

    database.close();

    if(database.isOpen())
        return false;
    return true;
}

bool Database::populate()
{
    // If database is already populated
    if(containsData())
        return true;

    // Drop Tables - Create Tables - Insert Data
    if (!dropTables() || !createTables() || !doStandartInserts())
        return false;

    return true;
}

bool Database::containsData()
{
    QSqlQuery query;
    bool res = query.prepare("SELECT count(*) FROM sqlite_master WHERE type = 'table'");
    res = query.exec();

    int count = 0;
    while(query.next())
    {
        count = query.value(0).toInt();
    }

    if (!res)
    {
        qDebug() << "Res from get users count = " << res << "\n";
        return false;
    }

    qDebug() << "Count of tables " << count;

    if (count != StandardQueries::createTables.count())
        return false;

    return true;
}

bool Database::dropTables()
{
    QSqlQuery query;
    bool res = false;
    for(int i = 0; i < StandardQueries::dropTables.length(); i++)
    {
        res = query.exec(StandardQueries::dropTables.at(i));
        qDebug() << "Res from Drop tables = " << res << "/n";
    }
    return res;
}

bool Database::createTables()
{
    QSqlQuery query;
    bool res = false;
    for(int i = 0; i < StandardQueries::createTables.length(); i++)
    {
        res = query.exec(StandardQueries::createTables.at(i));
        qDebug() << "Res from Create tables = " << res << "/n";
    }
    return res;
}

bool Database::doStandartInserts()
{
    QSqlQuery query;
    bool res = false;
    for(int i = 0; i < StandardQueries::insertQueries.length(); i++)
    {
        res = query.exec(StandardQueries::insertQueries.at(i));
        qDebug() << "Res from Insert queries = " << res << "/n";
    }
    return res;
}

///         ***         ///         API for app         ///         ***         ///

bool Database::insertUser(User *user)
{
    QSqlQuery query;
    bool res = query.prepare("INSERT INTO users(id, username, password, is_admin, is_active, name,"
                             " surname, address) VALUES(:id, :username, :password, :is_admin, :is_active, :name,"
                             " :surname, :address); ");

    query.bindValue(":id", user->id);
    query.bindValue(":username", user->username);
    query.bindValue(":password", user->password);
    query.bindValue(":is_admin", user->isAdmin);
    query.bindValue(":is_active", user->isActive);
    query.bindValue(":name", user->name);
    query.bindValue(":surname", user->surname);
    query.bindValue(":address", user->address);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in get users = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::updateUser(User *user)
{
    QSqlQuery query;
    bool res = query.prepare("UPDATE users SET username=?, password=?, is_admin=?, "
                             "is_active=?, name=?, surname=?, address=? WHERE id="
                             + QString::number(user->id) + "; ");

    query.addBindValue(user->username);
    query.addBindValue(user->password);
    query.addBindValue(user->isAdmin);
    query.addBindValue(user->isActive);
    query.addBindValue(user->name);
    query.addBindValue(user->surname);
    query.addBindValue(user->address);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in update user = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getUser(User *user, int user_id)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT * FROM users WHERE id=" + QString::number(user_id));
    res = query.exec();

    while(query.next())
    {
        user->id = query.value(0).toInt();
        user->username = query.value(1).toString();
        user->password = query.value(2).toString();
        user->isAdmin = query.value(3).toInt();
        user->isActive = query.value(4).toInt();
        user->name = query.value(5).toString();
        user->surname = query.value(6).toString();
        user->address = query.value(7).toString();

        qDebug() << "User[" << user->id << "] data = " << user->username << " " << user->password << " "
                 << user->isAdmin << " " << user->isActive << " " << user->name << " " << user->surname << " "
                 << user->address;
    }

    if(!res)
    {
        qDebug() << "Error in get users = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getUsersCount(int& count)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT count(*) FROM users");
    res = query.exec();

    count = -1;
    while(query.next())
    {
        count = query.value(0).toInt();
    }

    if(!res)
    {
        qDebug() << "Error in get users count = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getLastUserId(int &last_id)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT id FROM users ORDER BY id DESC;");
    res = query.exec();

    last_id = -1;
    while(query.next())
    {
        last_id = query.value(0).toInt();
        qDebug() << "ids from query = " << last_id;
        break;
    }

    if(!res)
    {
        qDebug() << "Error in get last user id = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::deleteUser(int user_id)
{
    QSqlQuery query;
    bool res = query.prepare("DELETE FROM users WHERE id=" + QString::number(user_id));
    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in delete user = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getUserByUsername(User* user, QString username)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT * FROM users WHERE username='" + username + "';");
    res = query.exec();

    while(query.next())
    {
        user->id = query.value(0).toInt();
        user->username = query.value(1).toString();
        user->password = query.value(2).toString();
        user->isAdmin = query.value(3).toInt();
        user->isActive = query.value(4).toInt();
        user->name = query.value(5).toString();
        user->surname = query.value(6).toString();
        user->address = query.value(7).toString();

        qDebug() << "User[" << user->id << "] data = " << user->username << " " << user->password << " "
                 << user->isAdmin << " " << user->isActive << " " << user->name << " " << user->surname << " "
                 << user->address;
    }

    if(!res)
    {
        qDebug() << "Error in get users = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::addUserDepartment(int user_id, int dep_id)
{
    Department dep;
    if(!getDepartment(&dep, dep_id))    //  if dep not exists
        return false;

    QSqlQuery query;
    bool res = query.prepare("INSERT INTO user_dep(user_id, dep_id VALUES(:user_id, :dep_id );");

    query.bindValue(":user_id", user_id);
    query.bindValue(":dep_id", dep_id);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in addUserDepartment = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::deleteUserDepartments(int user_id)
{
    QSqlQuery query;
    bool res = query.prepare("DELETE FROM user_dep WHERE user_id=" + QString::number(user_id));
    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in deleteUserDepartments = " << query.lastError().text();
        return false;
    }

    return true;
}

bool Database::getUserDepartments(Department* deps, int user_id)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT * FROM user_dep WHERE user_id=" + QString::number(user_id));
    res = query.exec();

    while(query.next())
    {
        deps->id = query.value(0).toInt();
        deps->name = query.value(1).toString();
        deps->isOperating = query.value(2).toBool();
        deps->taxTypeId = query.value(3).toInt();
        deps->isActive = query.value(4).toInt();

        qDebug() << "Department[" << deps->id << "] data = " << deps->name << " " << deps->isOperating << " "
                 << deps->taxTypeId << " " << deps->isActive;
    }

    if(!res)
    {
        qDebug() << "Error in getDepartment = " << query.lastError().text();
        return false;
    }
    return true;
}

//  Departments API
bool Database::insertDepartment(Department *dep)
{
    QSqlQuery query;
    bool res = query.prepare("INSERT INTO departments(id, name, is_operating, tax_type_id, is_active)"
                             " VALUES(:id, :name, :is_operating, :tax_type_id, :is_active );");

    query.bindValue(":id", dep->id);
    query.bindValue(":name", dep->name);
    query.bindValue(":is_operating", dep->isOperating);
    query.bindValue(":tax_type_id", dep->taxTypeId);
    query.bindValue(":is_active", dep->isActive);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in insertDepartment = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::updateDepartment(Department *dep)
{
    QSqlQuery query;
    bool res = query.prepare("UPDATE departments SET name=?, is_operating=?, tax_type_id=?, "
                             "is_active=? WHERE id="
                             + QString::number(dep->id) + "; ");

    query.addBindValue(dep->name);
    query.addBindValue(dep->isOperating);
    query.addBindValue(dep->taxTypeId);
    query.addBindValue(dep->isActive);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in updateDepartment = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getDepartment(Department *dep, int dep_id)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT * FROM departments WHERE id=" + QString::number(dep_id));
    res = query.exec();

    while(query.next())
    {
        dep->id = query.value(0).toInt();
        dep->name = query.value(1).toString();
        dep->isOperating = query.value(2).toBool();
        dep->taxTypeId = query.value(3).toInt();
        dep->isActive = query.value(4).toInt();

        qDebug() << "Department[" << dep->id << "] data = " << dep->name << " " << dep->isOperating << " "
                 << dep->taxTypeId << " " << dep->isActive;
    }

    if(!res)
    {
        qDebug() << "Error in getDepartment = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getDepartmentsCount(int& count)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT count(*) FROM departments");
    res = query.exec();

    count = -1;
    while(query.next())
    {
        count = query.value(0).toInt();
    }

    if(!res)
    {
        qDebug() << "Error in getDepartmentsCount = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getLastDepartmentId(int& last_id)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT id FROM departments ORDER BY id DESC;");
    res = query.exec();

    last_id = -1;
    while(query.next())
    {
        last_id = query.value(0).toInt();
        qDebug() << "ids from query = " << last_id;
        break;
    }

    if(!res)
    {
        qDebug() << "Error in getLastDepartmentId = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::deleteDepartment(int dep_id)
{
    //  TODO    //  need to delete goods in dep_id department and disconnect cashiers from dep_id department
//    if(!deleteDepartmentProducts(dep_id))
//        return false;

    QSqlQuery query;
    bool res = query.prepare("DELETE FROM departments WHERE id=" + QString::number(dep_id));
    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in deleteDepartment = " << query.lastError().text();
        return false;
    }

    return true;
}

//  Measurement Units API
bool Database::getMeasurementUnits(MeasurementUnit* units, int& count)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT * FROM measurement_units;");
    res = query.exec();

    count = 0;
    while(query.next())
    {
        units->id = query.value(0).toInt();
        units->name = query.value(1).toString();

        qDebug() << "User[" << units->id << "] data = " << units->name;
        count++;
    }

    if(!res)
    {
        qDebug() << "Error in getMeasurementUnits = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getMeasurementUnitsCount(int& count)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT count(*) FROM measurement_units;");
    res = query.exec();

    count = -1;
    while(query.next())
    {
        count = query.value(0).toInt();
    }

    if(!res)
    {
        qDebug() << "Error in get getMeasurementUnitsCount = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getMeasurementUnit(MeasurementUnit* unit, int measUnitID)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT * FROM measurement_units WHERE id=" + QString::number(measUnitID));
    res = query.exec();

    while(query.next())
    {
        unit->id = query.value(0).toInt();
        unit->name = query.value(1).toString();

        qDebug() << "User[" << unit->id << "] data = " << unit->name;
    }

    if(!res)
    {
        qDebug() << "Error in getMeasurementUnit = " << query.lastError().text();
        return false;
    }
    return true;
}

//  Products API
bool Database::insertProduct(Product* product)
{
    QSqlQuery query;
    bool res = query.prepare("INSERT INTO goods(id, name, code, measurement_id, price, discount,"
                             " dep_id, adg_code) VALUES(:id, :name, :code, :measurement_id, :price, :discount,"
                             " :dep_id, :adg_code); ");

    query.bindValue(":id", product->id);
    query.bindValue(":name", product->name);
    query.bindValue(":code", product->code);
    query.bindValue(":measurement_id", product->measurementUnitId);
    query.bindValue(":price", product->price);
    query.bindValue(":discount", product->discount);
    query.bindValue(":dep_id", product->departmentID);
    query.bindValue(":adg_code", product->atgaCode);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in insertProduct = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::updateProduct(Product product)
{
    QSqlQuery query;
    bool res = query.prepare("UPDATE goods name=?, code=?, measurement_id=?, price=?, discount=?,"
                             " dep_id=?, adg_code=? WHERE id="
                             + QString::number(product.id) + "; ");

    query.addBindValue(product.name);
    query.addBindValue(product.code);
    query.addBindValue(product.measurementUnitId);
    query.addBindValue(product.price);
    query.addBindValue(product.discount);
    query.addBindValue(product.departmentID);
    query.addBindValue(product.atgaCode);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in updateProduct = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getProduct(Product* ptoduct, int prodID)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT * FROM goods WHERE id=" + QString::number(prodID));
    res = query.exec();

    while(query.next())
    {
        ptoduct->id = query.value(0).toInt();
        ptoduct->name = query.value(1).toString();
        ptoduct->code = query.value(2).toString();
        ptoduct->measurementUnitId = query.value(3).toInt();
        ptoduct->price = query.value(4).toInt();
        ptoduct->discount = query.value(5).toDouble();
        ptoduct->departmentID = query.value(6).toString();
        ptoduct->atgaCode = query.value(7).toString();

        qDebug() << "Ptoduct[" << ptoduct->id << "] data = " << ptoduct->name << " " << ptoduct->code << " "
                 << ptoduct->measurementUnitId << " " << ptoduct->price << " " << ptoduct->discount << " " << ptoduct->departmentID << " "
                 << ptoduct->atgaCode;
    }

    if(!res)
    {
        qDebug() << "Error in getProduct = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getProductsCount(int& count)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT count(*) FROM goods;");
    res = query.exec();

    count = -1;
    while(query.next())
    {
        count = query.value(0).toInt();
    }

    if(!res)
    {
        qDebug() << "Error in get getProductsCount = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::getLastProductId(int& lastID)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT id FROM goods ORDER BY id DESC;");
    res = query.exec();

    lastID = -1;
    while(query.next())
    {
        lastID = query.value(0).toInt();
        qDebug() << "ids from query = " << lastID;
        break;
    }

    if(!res)
    {
        qDebug() << "Error in getLastProductId = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::deleteProduct(int prodID)
{
    QSqlQuery query;
    bool res = query.prepare("DELETE FROM goods WHERE id=" + QString::number(prodID));
    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in deleteProduct = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::deleteDepartmentProducts(int depID)
{
    QSqlQuery query;
    bool res = query.prepare("DELETE FROM goods WHERE dep_id=" + QString::number(depID));
    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in deleteDepartmentProducts = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::deleteAllProducts()
{
    QSqlQuery query;
    bool res = query.prepare("DELETE * FROM goods;");
    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in deleteAllProducts = " << query.lastError().text();
        return false;
    }
    return true;
}
