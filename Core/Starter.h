#ifndef STARTER_H
#define STARTER_H

#include <QThread>
#include <QApplication>

#include "CoreGlobals.h"

class Starter : public QThread
{
    Q_OBJECT

public:
    Starter();

    static Starter* get();

    static void runStarter(QThread *parentThread);

    static void quitStarter();

private slots:

    void initJob();

private: // Main Parts

    void initDatabase();

private: // Helpers

    bool createDatabase();

signals:
    void databaseCreated(bool);

private:
    QThread* m_parentThread;
};

#endif // STARTER_H
