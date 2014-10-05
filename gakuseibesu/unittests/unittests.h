#ifndef UNITTESTS_H
#define UNITTESTS_H
#include <QtTest/QtTest>
#include "../database.h"

class UnitTests : public QObject
{
    Q_OBJECT
private slots:
    void ProfileInsertTest();
};

#endif // UNITTESTS_H
