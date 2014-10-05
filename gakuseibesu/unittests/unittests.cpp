
#include "unittests.h"

void UnitTests::ProfileInsertTest()
{
    Database *db = new Database();
    Profile profile;
    profile.Id = 0;
    profile.Firstname = "Иван";
    profile.Lastname = "Иванов";
    profile.Patronym = "Иванович";
    profile.Birthday = QDate(1970, 1, 1);
    profile.Document = "паспорт 1234 123456";
    profile.Telephone = 89876543211;
    profile.Sex = 0;

    Profile profile2;
    profile2.Id = 1;
    profile2.Firstname = "Иван";
    profile2.Lastname = "Иванов";
    profile2.Patronym = "Иванович";
    profile2.Birthday = QDate(1970, 1, 1);
    profile2.Document = "паспорт 1234 123456";
    profile2.Telephone = 89876543211;
    profile2.Sex = 0;

    /*Grade grade;
    grade.PeopleId = 0;
    grade.Id = 1;
    grade.Date = QDate(2000, 1, 1);*/

    auto insId0 = db->AddProfile(profile).toInt();
    //auto insId1 = db->AddGrade(grade).toInt();
    auto insId2 = db->AddProfile(profile2).toInt();
    auto profileList = db->AllProfiles();
    QVERIFY(profileList.count() == 2);
    /*auto gradeList = db->GetGradesByProfile(profile);
    QVERIFY(gradeList.count() == 1);*/
    db->RemoveDatabase();
}

QTEST_MAIN(UnitTests)
//#include "UnitTests.moc"
