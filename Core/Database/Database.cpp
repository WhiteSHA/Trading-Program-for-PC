#include "Database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include "CoreGlobals.h"

Database::Database()
{

}

Database::~Database()
{
//    close();
}

bool Database::open()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("F:/Qt Projects/Shop/shop.db");

    if (!database.open())
        return false;
    return true;
}

bool Database::close()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("F:/Qt Projects/Shop/shop.db");

    database.close();

    if(database.isOpen())
        return false;
    return true;
}

bool Database::populate()
{
    // If database is already populated
//    if (m_impl->containsData())
//        return true;

    // Drop Tables - Create Tables - Insert Data
//    if (!m_impl->dropTables() || !m_impl->createTables() || !m_impl->doStandardInserts())
//        return false;

    return true;
}

bool Database::insertUser(User *user)
{
    Q_UNUSED(user);

    return true;
}
