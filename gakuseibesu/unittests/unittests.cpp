
#include "unittests.h"

void UnitTests::DatabaseTest()
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
    profile2.Firstname = "Петр";
    profile2.Lastname = "Иванов";
    profile2.Patronym = "Иванович";
    profile2.Birthday = QDate(1970, 1, 1);
    profile2.Document = "паспорт 1234 123456";
    profile2.Telephone = 89876543211;
    profile2.Sex = 0;

    Grade grade;
    grade.PeopleId = 0;
    grade.Id = 1;
    grade.Date = QDate(2000, 1, 1);

    int insId0 = db->AddProfile(profile).toInt();
    int insId1 = db->AddGrade(grade).toInt();
    int insId2 = db->AddProfile(profile2).toInt();
    auto profileList = db->AllProfiles();
    QVERIFY(profileList.count() == 2);

    Profile extractedProfile = db->GetUserById(insId2);

    QVERIFY(extractedProfile.Firstname == "Петр");

    auto gradeList = db->GetGradesByProfile(profile);
    QVERIFY(gradeList.count() == 1);

    auto user = db->GetUserById(1);
    QVERIFY(user.Firstname == profile2.Firstname);

    //it's a trap!
    profile.Sex = true;
    QVERIFY(db->UpdateProfile(profile));

    auto updatedUser = db->GetUserById(0);
    QVERIFY(updatedUser.Sex);

    grade.PeopleId = 1;
    QVERIFY(db->UpdateGrade(grade));

    auto gradeList2 = db->GetGradesByProfile(profile2);
    QVERIFY(gradeList2.count() == 1);

    db->DeleteProfile(profile);
    auto allProfiles = db->AllProfiles();
    QVERIFY(allProfiles.count() == 1);

    db->DeleteGrade(grade);

    auto gradeList3 = db->GetGradesByProfile(profile2);
    QVERIFY(gradeList3.count() == 0);

    db->RemoveDatabase();
}

QTEST_MAIN(UnitTests)
//#include "UnitTests.moc"
