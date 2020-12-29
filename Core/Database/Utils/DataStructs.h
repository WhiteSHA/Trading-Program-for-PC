#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QtGlobal>
#include <QString>

struct User
{
    int id;
    QString username = "";
    QString password = "";
    bool isAdmin = false;
    bool isActiv = false;
    QString name = "";
    QString surname = "";
    QString address = "";
};

#endif // DATASTRUCTS_H
