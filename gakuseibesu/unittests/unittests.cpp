
#include "unittests.h"

void UnitTests::DatabaseTest()
{
    Database *db = Database::GetInstance();
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
    profile2.Firstname = "Petr";
    profile2.Lastname = "Иванов";
    profile2.Patronym = "Иванович";
    profile2.Birthday = QDate(1970, 1, 1);
    profile2.Document = "паспорт 1234 123456";
    profile2.Telephone = 89876543211;
    profile2.Sex = 0;

    Grade grade;
    grade.PeopleId = 0;
    grade.Id = 0;
    grade.Date = QDate(2000, 1, 1);

    Grade grade2;
    grade2.PeopleId = 1;
    grade2.Id = 1;
    grade2.Date = QDate(2002, 1, 1);
    grade2.GradeString = "string1";

    int insId0 = db->AddProfile(profile).toInt();
    int insId1 = db->AddGrade(grade).toInt();
    int insId2 = db->AddProfile(profile2).toInt();
    db->AddGrade(grade2);
    auto profileList = db->AllProfiles();
    QVERIFY(profileList.count() == 2);

    Profile extractedProfile = db->GetUserById(insId2);

    QVERIFY(extractedProfile.Firstname == "Petr");

    auto gradeList = db->GetGradesByProfile(profile.Id);
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

    auto gradeList2 = db->GetGradesByProfile(profile2.Id);
    QVERIFY(gradeList2.count() == 2);

    Profile profileToFind = Profile();
    profileToFind.Lastname = "Иванов";
    profileToFind.Sensei = "yoda";
    QList<Database::SearchFields> searchFields = QList<Database::SearchFields>();
    searchFields.append(Database::SearchFields::lastname);
    auto findResults = db->FindProfiles(searchFields, profileToFind, QDate::currentDate(), QDate::currentDate(), Grade(), QDate(), QDate());
    QVERIFY(findResults.count() == 2);

    Profile profile3;
    profile3.Id = 2;
    profile3.Firstname = "a";
    profile3.Lastname = "b";
    profile3.Patronym = "c";
    profile3.Birthday = QDate(1989, 1, 1);
    profile3.Document = "d";
    profile3.Telephone = 8;
    profile3.Sex = 0;

    db->AddProfile(profile3);

    Profile profile4;
    profile4.Id = 3;
    profile4.Firstname = "a";
    profile4.Lastname = "b";
    profile4.Patronym = "c";
    profile4.Birthday = QDate(1981, 1, 1);
    profile4.Document = "d";
    profile4.Telephone = 8;
    profile4.Sex = 0;

    db->AddProfile(profile4);
    QList<Database::SearchFields> searchFields2 = QList<Database::SearchFields>();
    searchFields2.append(Database::SearchFields::date);
    auto findResults2 = db->FindProfiles(searchFields2, Profile(), QDate(1980, 1, 1), QDate(1990, 1, 1), Grade(), QDate(), QDate());
    QVERIFY(findResults2.count() == 2);

    QList<Database::SearchFields> searchFields3 = QList<Database::SearchFields>();
    searchFields3.append(Database::SearchFields::grade);
    Grade gradeToSearch = Grade();
    gradeToSearch.GradeString = "string1";
    auto findResults3 = db->FindProfiles(searchFields3, Profile(), QDate(), QDate(), gradeToSearch, QDate(), QDate());
    QVERIFY(findResults3.count() == 1);
    QList<Database::SearchFields> searchFields4 = QList<Database::SearchFields>();
    searchFields4.append(Database::SearchFields::gradedate);
    auto findResults4 = db->FindProfiles(searchFields4, Profile(), QDate(), QDate(), Grade(), QDate(1999, 1, 1), QDate(2003, 1, 1));
    QVERIFY(findResults4.count() == 1);

    db->DeleteProfile(profile.Id);
    auto allProfiles = db->AllProfiles();
    QVERIFY(allProfiles.count() == 3);

    db->DeleteGrade(grade.Id);

    auto gradeList3 = db->GetGradesByProfile(profile2.Id);
    QVERIFY(gradeList3.count() == 1);


    db->RemoveDatabase();
}

QTEST_MAIN(UnitTests)
//#include "UnitTests.moc"
