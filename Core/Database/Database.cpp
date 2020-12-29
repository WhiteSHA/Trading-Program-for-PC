#include "Database.h"
#include <QSqlDatabase>
#include <QSqlQuery>

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
    {
        return false;
    }
    else
    {
        QSqlQuery query;
        query.prepare("CREATE TABLE users (id INT PRIMARY KEY NOT NULL,username TEXT,password TEXT,"
                      "type_id INT,is_operating INT,is_active INT);");
        query.exec();

//        query.clear();
//        query.prepare("INSERT INTO users (id, username, password, type_id, is_operating, is_active) "
//                      "VALUES (:id, :username, :password, :type_id, :is_operating, :is_active)");
//        query.bindValue(":id", 2);
//        query.bindValue(":username", "test2");
//        query.bindValue(":password", "testPass2");
//        query.bindValue(":type_id", "1");
//        query.bindValue(":is_operating", "0");
//        query.bindValue(":is_active", "0");
//        query.exec();

        query.clear();

        query.prepare("DELETE FROM users WHERE id=2;");
        query.exec();
    }
    return true;
}

bool Database::close()
{
    return 0;
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
