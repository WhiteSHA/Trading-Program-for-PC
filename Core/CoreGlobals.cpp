#include "CoreGlobals.h"

namespace CoreGlobals   // Global variable definitions
{
    QApplication* app = 0;

    Database *g_database = 0;
}

namespace CoreGlobals // Global function declarations
{

}

Database& db()
{
    return *CoreGlobals::g_database;
}
