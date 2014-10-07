#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QList>
#include "profile.h"
#include "grade.h"

class Database
{
public:
    Database();
    QVariant AddProfile(Profile profile);
    QVariant AddGrade(Grade grade);

    bool UpdateProfile(Profile profile);
    bool UpdateGrade(Grade grade);

    bool DeleteProfile(Profile profile);
    bool DeleteGrade(Grade grade);

    QList<Grade> GetGradesByProfile(Profile profile);
    QList<Profile> AllProfiles();
    Profile GetUserById(int id);

    void RemoveDatabase();
private:
    void LogError(QSqlError error);
    const char* dbName = ":gakusei:";
};

#endif // DATABASE_H
