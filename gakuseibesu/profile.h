#ifndef PROFILE_H
#define PROFILE_H
#include <QString>
#include <QDate>
class Profile
{
public:
    int Id;
    QString Firstname;
    QString Lastname;
    QString Patronym;
    QDate Birthday;
    QString Document;
    QString Addres;
    QString Telephone;
    bool Sex;
    QString Sensei;
    Profile() {}
};

#endif // PROFILE_H
