#ifndef GRADE_H
#define GRADE_H
#include <QString>
#include <QDate>

class Grade
{
public:
    int Id;
    QDate Date;
    int PeopleId;
    Grade() {}
};
#endif // GRADE_H
