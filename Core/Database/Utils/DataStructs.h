#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QtGlobal>
#include <QString>
#include <Database/Utils/Enums.h>

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

struct MeasurementUnit
{
    int id;
    QString name;
};

struct Product
{
    int id;
    QString name = "";
    QString code = "";
    int measurementUnitId;
    double price = 0.0;
    double discount = 0.0;
    QString departmentID = "";
    QString atgaCode = "";
};

struct Action
{
    ActionType actionType = ActionType::TO_INSERT;
    int id = -1;
};

#endif // DATASTRUCTS_H
