#include <QDebug>
#include "database.h"

Database::Database()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open())
           LogError(db.lastError());
    QStringList tables = db.tables();
    if(!tables.contains("people"))
    {
        QSqlQuery q;
        if (!q.exec(QLatin1String("create table people(id integer primary key, firstname varchar, lastname varchar, patronym varchar, birthday date, document varchar, addres varchar, telephone integer, sex integer, sensei varchar)")))
            LogError(q.lastError());
    }
    if(!tables.contains("grades"))
    {
        QSqlQuery q;
        if (!q.exec(QLatin1String("create table grades(id integer primary key, peopleId varchar, date date)")))
            LogError(q.lastError());
    }

}

QVariant Database::AddProfile(Profile profile)
{
    QSqlQuery q;
    if(!q.prepare(QLatin1String("insert into people(id, firstname, lastname, patronym, birthday, document, addres, telephone, sex, sensei) values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)")))
        LogError(q.lastError());
    q.addBindValue(profile.Id);
    q.addBindValue(profile.Firstname);
    q.addBindValue(profile.Lastname);
    q.addBindValue(profile.Patronym);
    q.addBindValue(profile.Birthday);
    q.addBindValue(profile.Document);
    q.addBindValue(profile.Addres);
    q.addBindValue(profile.Telephone);
    q.addBindValue(profile.Sex);
    q.addBindValue(profile.Sensei);

    q.exec();
    LogError(q.lastError());
    return q.lastInsertId();
}

QVariant Database::AddGrade(Grade grade)
{
    QSqlQuery q;
    if(!q.prepare(QLatin1String("insert into grades(id, peopleId, date) values(?, ?, ?)")))
        LogError(q.lastError());
    q.addBindValue(grade.Id);
    q.addBindValue(grade.PeopleId);
    q.addBindValue(grade.Date);
    q.exec();
    LogError(q.lastError());
    return q.lastInsertId();
}

bool Database::UpdateProfile(Profile profile)
{
    QSqlQuery q;
    if(!q.prepare(QLatin1String("update people set firstname=?, lastname=?, patronym=?, birthday=?, document=?, addres=?, telephone=?, sex=?, sensei=? where id=?")))
        LogError(q.lastError());
    q.addBindValue(profile.Firstname);
    q.addBindValue(profile.Lastname);
    q.addBindValue(profile.Patronym);
    q.addBindValue(profile.Birthday);
    q.addBindValue(profile.Document);
    q.addBindValue(profile.Addres);
    q.addBindValue(profile.Telephone);
    q.addBindValue(profile.Sex);
    q.addBindValue(profile.Sensei);
    q.addBindValue(profile.Id);

    auto res = q.exec();
    LogError(q.lastError());
    return res;
}

bool Database::UpdateGrade(Grade grade)
{
    QSqlQuery q;
    if(!q.prepare(QLatin1String("update grades set peopleId=?, date=? where id=?")))
        LogError(q.lastError());
    q.addBindValue(grade.PeopleId);
    q.addBindValue(grade.Date);
    q.addBindValue(grade.Id);
    auto res = q.exec();
    LogError(q.lastError());
    return res;
}

bool Database::DeleteProfile(Profile profile)
{
    QSqlQuery q;
    if(!q.prepare(QLatin1String("delete from people where id=?")))
        LogError(q.lastError());
    q.addBindValue(profile.Id);
    return q.exec();
}

bool Database::DeleteGrade(Grade grade)
{
    QSqlQuery q;
    if(!q.prepare(QLatin1String("delete from grades where id=?")))
        LogError(q.lastError());
    q.addBindValue(grade.Id);
    return q.exec();
}

QList<Grade> Database::GetGradesByProfile(Profile profile)
{
    auto result = QList<Grade>();
    QSqlQuery q;
    if(!q.prepare(QLatin1String("select * from grades where peopleId=?")))
        LogError(q.lastError());
    q.addBindValue(profile.Id);
    q.exec();
    while (q.next()) {
        QSqlRecord rec = q.record();
        Grade grade;

        int idIndex = rec.indexOf("id");
        int dateIndex = rec.indexOf("date");

        Grade gradeRec;
        gradeRec.Id = q.value(idIndex).toInt();
        gradeRec.PeopleId = profile.Id;
        gradeRec.Date = q.value(dateIndex).toDate();

        result.append(gradeRec);
    }
    return result;
}

QList<Profile> Database::AllProfiles()
{
    auto result = QList<Profile>();
    QSqlQuery q;
    if(!q.prepare(QLatin1String("select * from people")))
        LogError(q.lastError());
    q.exec();
    while (q.next()) {
        QSqlRecord rec = q.record();
        Profile profile;

        int idIndex = rec.indexOf("id");
        int firstnameIndex = rec.indexOf("firstname");
        int lastnameIndex = rec.indexOf("lastname");
        int patronymIndex = rec.indexOf("patronym");
        int birthdayIndex = rec.indexOf("birthday");
        int documentIndex = rec.indexOf("document");
        int addresIndex = rec.indexOf("addres");
        int telIndex = rec.indexOf("telephone");
        int sexIndex = rec.indexOf("sex");
        int senseiIndex = rec.indexOf("sensei");

        profile.Id = q.value(idIndex).toInt();
        profile.Firstname = q.value(firstnameIndex).toString();
        profile.Lastname = q.value(lastnameIndex).toString();
        profile.Patronym = q.value(patronymIndex).toString();
        profile.Birthday = q.value(birthdayIndex).toDate();
        profile.Document = q.value(documentIndex).toString();
        profile.Addres = q.value(addresIndex).toString();
        profile.Telephone = q.value(telIndex).toUInt();
        profile.Sex = q.value(sexIndex).toBool();
        profile.Sensei = q.value(senseiIndex).toString();

        result.append(profile);
    }
    return result;
}

Profile Database::GetUserById(int id)
{
    QSqlQuery q;
    if(!q.prepare(QLatin1String("select * from people where id=?")))
        LogError(q.lastError());
    q.addBindValue(id);
    q.exec();
    if (q.next()) {
        QSqlRecord rec = q.record();
        Profile profile;

        int idIndex = rec.indexOf("id");
        int firstnameIndex = rec.indexOf("firstname");
        int lastnameIndex = rec.indexOf("lastname");
        int patronymIndex = rec.indexOf("patronym");
        int birthdayIndex = rec.indexOf("birthday");
        int documentIndex = rec.indexOf("document");
        int addresIndex = rec.indexOf("addres");
        int telIndex = rec.indexOf("telephone");
        int sexIndex = rec.indexOf("sex");
        int senseiIndex = rec.indexOf("sensei");

        profile.Id = q.value(idIndex).toInt();
        profile.Firstname = q.value(firstnameIndex).toString();
        profile.Lastname = q.value(lastnameIndex).toString();
        profile.Patronym = q.value(patronymIndex).toString();
        profile.Birthday = q.value(birthdayIndex).toDate();
        profile.Document = q.value(documentIndex).toString();
        profile.Addres = q.value(addresIndex).toString();
        profile.Telephone = q.value(telIndex).toUInt();
        profile.Sex = q.value(sexIndex).toBool();
        profile.Sensei = q.value(senseiIndex).toString();

        return profile;
    }
    return Profile();
}

void Database::RemoveDatabase()
{
    QSqlQuery q;
    if(!q.exec(QLatin1String("drop table grades")))
        LogError(q.lastError());
    QSqlQuery q2;
    if(!q2.exec(QLatin1String("drop table people")))
        LogError(q2.lastError());
    QFile::remove(dbName);
}

void Database::LogError(QSqlError error)
{
    qDebug(error.text().toStdString().c_str());
}


