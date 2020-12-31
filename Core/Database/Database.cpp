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
#ifdef DEBUG_UTILS
        qDebug() << "Res from get users count = " << res << "\n";
#endif
        return false;
    }

#ifdef DEBUG_UTILS
    qDebug() << "Count of tables " << count;
#endif

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
    Q_UNUSED(user);

    return true;
}

bool Database::updateUser(User *user)
{
    Q_UNUSED(user);

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
        user->isActiv = query.value(4).toInt();
        user->name = query.value(5).toString();
        user->surname = query.value(6).toString();
        user->address = query.value(7).toString();

        qDebug() << "User[" << user->id << "] data = " << user->username << " " << user->password << " "
                 << user->isAdmin << " " << user->isActiv << " " << user->name << " " << user->surname << " "
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
