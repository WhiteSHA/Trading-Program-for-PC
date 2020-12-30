#include "Database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
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

bool Database::containsData()
{
    QSqlQuery query;
    int res = query.prepare("SELECT count(*) FROM users");
    qDebug() << "res of query = " << res;
    res = query.exec();

    qDebug() << "res of query = " << res;
    qDebug() << "Query size = " << query.size();
    qDebug() << "Count of tables = " << query.value(0).toInt();
    qDebug() << "Count of tables = " << query.value(1).toInt();
    qDebug() << "Count of tables = " << query.value(2).toInt();

    if (res != 1)
    {
#ifdef DEBUG_UTILS
        qDebug() << "Res from get users count = " << res << "\n";
#endif
        return false;
    }

#ifdef DEBUG_UTILS
    printf("Count of tables %d\n", count);
#endif

//    if (count != StandardQueries::createTables.count())
//        return false;

    return true;
}

bool Database::populate()
{
    // If database is already populated
    if(containsData())
        return true;

    // Drop Tables - Create Tables - Insert Data
//    if (!m_impl->dropTables() || !m_impl->createTables() || !m_impl->doStandardInserts())
//        return false;

    return true;
}

///         ***         ///         API for app         ///         ***         ///

bool Database::insertUser(User *user)
{
    Q_UNUSED(user);

    return true;
}
