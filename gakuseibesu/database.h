#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QList>
#include "profile.h"
#include "grade.h"

class Database
{
public:
    static Database *GetInstance();
    QVariant AddProfile(Profile profile);
    QVariant AddGrade(Grade grade);

    bool UpdateProfile(Profile profile);
    bool UpdateGrade(Grade grade);

    bool DeleteProfile(int profileId);
    bool DeleteGrade(int gradeId);

    QList<Grade> GetGradesByProfile(int id);
    QList<Profile> AllProfiles();
    QList<Profile> FindProfiles(Profile targetProf, QDate beginDate, QDate endDate, Grade targetGrade);
    Profile GetUserById(int id);
    Grade GetGradeById(int id);
    void RemoveDatabase();
private:
    Database();
    static Database *instance;
    void LogError(QSqlError error);
    const char* dbName = ":gakusei:";
};

#endif // DATABASE_H
