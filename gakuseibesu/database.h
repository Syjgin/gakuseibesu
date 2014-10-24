#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QList>
#include "profile.h"
#include "grade.h"

class Database
{
public:
    enum SearchFields
    {
        firstname,
        lastname,
        patronym,
        document,
        addres,
        telephone,
        sex,
        sensei,
        date,
        grade,
        gradedate
    };

    static Database *GetInstance();
    QVariant AddProfile(Profile profile);
    QVariant AddGrade(Grade grade);

    bool UpdateProfile(Profile profile);
    bool UpdateGrade(Grade grade);

    bool DeleteProfile(int profileId);
    bool DeleteGrade(int gradeId);

    QList<Grade> GetGradesByProfile(int id);
    QList<Profile> AllProfiles();
    QList<Profile> FindProfiles(QList<SearchFields> searchFields, Profile searchPattern, QDate beginDate, QDate endDate, Grade targetGrade, QDate gradeBeginDate, QDate gradeEndDate);
    Profile GetUserById(int id);
    Grade GetGradeById(int id);
    void RemoveDatabase();
private:
    Database();
    static Database *instance;
    void LogError(QSqlError error);
    const char* dbName = ":gakusei:";
    void AddParameterToSearchQuery(QString valueName, QString value, QString &query, QList<QString> &bindValues);
};

#endif // DATABASE_H
