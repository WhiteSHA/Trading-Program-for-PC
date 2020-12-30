#ifndef COREGLOBALS_H
#define COREGLOBALS_H

#include <QSettings>
#include <QApplication>
#include "Core/Database/Database.h"


namespace CoreGlobals // Global variable declarations
{
    extern QApplication* app;

    extern Database* g_database;
}

namespace CoreGlobals // Global function declarations
{

}

Database& db();

#endif // COREGLOBALS_H
