
#include <algorithm>

#include "acutest.h"
#include "Config.h"

void test_Config_ParseActivities()
{

    std::pair<std::vector<Activity>, std::vector<std::string>> activitiesAndFacilitators = ParseActivitiesAndFacilitators("./config/activities.json");

    std::vector<Activity> activities = activitiesAndFacilitators.first;
    std::vector<std::string> facilitators = activitiesAndFacilitators.second;

    // Assertion for correct parsing of facilitators
    std::sort(facilitators.begin(), facilitators.end());
    TEST_ASSERT(facilitators == std::vector<std::string>({"Banks", "Glen", "Lock", "Numen", "Richards", "Shaw", "Singer", "Tyler", "Uther", "Zeldin"}));

    // Assertions for SLA100
    TEST_ASSERT(activities.at(0).Name == "SLA100");
    TEST_ASSERT(activities.at(0).Section == "A");
    TEST_ASSERT(activities.at(0).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(0).PreferredFacilitators == std::vector<std::string>({"Glen", "Lock", "Banks", "Zeldin"}));
    TEST_ASSERT(activities.at(0).OtherFacilitators == std::vector<std::string>({"Numen", "Richards"}));

    TEST_ASSERT(activities.at(1).Name == "SLA100");
    TEST_ASSERT(activities.at(1).Section == "B");
    TEST_ASSERT(activities.at(1).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(1).PreferredFacilitators == std::vector<std::string>({"Glen", "Lock", "Banks", "Zeldin"}));
    TEST_ASSERT(activities.at(1).OtherFacilitators == std::vector<std::string>({"Numen", "Richards"}));

    // Assertions for SLA191
    TEST_ASSERT(activities.at(2).Name == "SLA191");
    TEST_ASSERT(activities.at(2).Section == "A");
    TEST_ASSERT(activities.at(2).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(2).PreferredFacilitators == std::vector<std::string>({"Glen", "Lock", "Banks", "Zeldin"}));
    TEST_ASSERT(activities.at(2).OtherFacilitators == std::vector<std::string>({"Numen", "Richards"}));

    TEST_ASSERT(activities.at(3).Name == "SLA191");
    TEST_ASSERT(activities.at(3).Section == "B");
    TEST_ASSERT(activities.at(3).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(3).PreferredFacilitators == std::vector<std::string>({"Glen", "Lock", "Banks", "Zeldin"}));
    TEST_ASSERT(activities.at(3).OtherFacilitators == std::vector<std::string>({"Numen", "Richards"}));

    // Assertions for SLA201
    TEST_ASSERT(activities.at(4).Name == "SLA201");
    TEST_ASSERT(activities.at(4).Section == "A");
    TEST_ASSERT(activities.at(4).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(4).PreferredFacilitators == std::vector<std::string>({"Glen", "Banks", "Zeldin", "Shaw"}));
    TEST_ASSERT(activities.at(4).OtherFacilitators == std::vector<std::string>({"Numen", "Richards", "Singer"}));

    TEST_ASSERT(activities.at(5).Name == "SLA201");
    TEST_ASSERT(activities.at(5).Section == "B");
    TEST_ASSERT(activities.at(5).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(5).PreferredFacilitators == std::vector<std::string>({"Glen", "Banks", "Zeldin", "Shaw"}));
    TEST_ASSERT(activities.at(5).OtherFacilitators == std::vector<std::string>({"Numen", "Richards", "Singer"}));

    // Assertions for SLA291
    TEST_ASSERT(activities.at(6).Name == "SLA291");
    TEST_ASSERT(activities.at(6).Section == "A");
    TEST_ASSERT(activities.at(6).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(6).PreferredFacilitators == std::vector<std::string>({"Lock", "Banks", "Zeldin", "Singer"}));
    TEST_ASSERT(activities.at(6).OtherFacilitators == std::vector<std::string>({"Numen", "Richards", "Shaw", "Tyler"}));

    TEST_ASSERT(activities.at(7).Name == "SLA291");
    TEST_ASSERT(activities.at(7).Section == "B");
    TEST_ASSERT(activities.at(7).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(7).PreferredFacilitators == std::vector<std::string>({"Lock", "Banks", "Zeldin", "Singer"}));
    TEST_ASSERT(activities.at(7).OtherFacilitators == std::vector<std::string>({"Numen", "Richards", "Shaw", "Tyler"}));

    // Assertions for SLA303
    TEST_ASSERT(activities.at(8).Name == "SLA303");
    TEST_ASSERT(activities.at(8).Section == "A");
    TEST_ASSERT(activities.at(8).ExpectedEnrollment == 60);
    TEST_ASSERT(activities.at(8).PreferredFacilitators == std::vector<std::string>({"Glen", "Zeldin", "Banks"}));
    TEST_ASSERT(activities.at(8).OtherFacilitators == std::vector<std::string>({"Numen", "Singer", "Shaw"}));

    TEST_ASSERT(activities.at(9).Name == "SLA303");
    TEST_ASSERT(activities.at(9).Section == "B");
    TEST_ASSERT(activities.at(9).ExpectedEnrollment == 60);
    TEST_ASSERT(activities.at(9).PreferredFacilitators == std::vector<std::string>({"Glen", "Zeldin", "Banks"}));
    TEST_ASSERT(activities.at(9).OtherFacilitators == std::vector<std::string>({"Numen", "Singer", "Shaw"}));

    // Assertions for SLA304
    TEST_ASSERT(activities.at(10).Name == "SLA304");
    TEST_ASSERT(activities.at(10).Section == "A");
    TEST_ASSERT(activities.at(10).ExpectedEnrollment == 25);
    TEST_ASSERT(activities.at(10).PreferredFacilitators == std::vector<std::string>({"Glen", "Banks", "Tyler"}));
    TEST_ASSERT(activities.at(10).OtherFacilitators == std::vector<std::string>({"Numen", "Singer", "Shaw", "Richards", "Uther", "Zeldin"}));

    TEST_ASSERT(activities.at(11).Name == "SLA304");
    TEST_ASSERT(activities.at(11).Section == "B");
    TEST_ASSERT(activities.at(11).ExpectedEnrollment == 25);
    TEST_ASSERT(activities.at(11).PreferredFacilitators == std::vector<std::string>({"Glen", "Banks", "Tyler"}));
    TEST_ASSERT(activities.at(10).OtherFacilitators == std::vector<std::string>({"Numen", "Singer", "Shaw", "Richards", "Uther", "Zeldin"}));

    // Assertions for SLA394
    TEST_ASSERT(activities.at(12).Name == "SLA394");
    TEST_ASSERT(activities.at(12).Section == "A");
    TEST_ASSERT(activities.at(12).ExpectedEnrollment == 20);
    TEST_ASSERT(activities.at(12).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer"}));
    TEST_ASSERT(activities.at(12).OtherFacilitators == std::vector<std::string>({"Richards", "Zeldin"}));

    TEST_ASSERT(activities.at(13).Name == "SLA394");
    TEST_ASSERT(activities.at(13).Section == "B");
    TEST_ASSERT(activities.at(13).ExpectedEnrollment == 20);
    TEST_ASSERT(activities.at(13).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer"}));
    TEST_ASSERT(activities.at(13).OtherFacilitators == std::vector<std::string>({"Richards", "Zeldin"}));

    // Assertions for SLA449
    TEST_ASSERT(activities.at(14).Name == "SLA449");
    TEST_ASSERT(activities.at(14).Section == "A");
    TEST_ASSERT(activities.at(14).ExpectedEnrollment == 60);
    TEST_ASSERT(activities.at(14).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer", "Shaw"}));
    TEST_ASSERT(activities.at(14).OtherFacilitators == std::vector<std::string>({"Zeldin", "Uther"}));

    TEST_ASSERT(activities.at(15).Name == "SLA449");
    TEST_ASSERT(activities.at(15).Section == "B");
    TEST_ASSERT(activities.at(15).ExpectedEnrollment == 60);
    TEST_ASSERT(activities.at(15).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer", "Shaw"}));
    TEST_ASSERT(activities.at(15).OtherFacilitators == std::vector<std::string>({"Zeldin", "Uther"}));

    // Assertions for SLA451
    TEST_ASSERT(activities.at(16).Name == "SLA451");
    TEST_ASSERT(activities.at(16).Section == "A");
    TEST_ASSERT(activities.at(16).ExpectedEnrollment == 100);
    TEST_ASSERT(activities.at(16).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer", "Shaw"}));
    TEST_ASSERT(activities.at(16).OtherFacilitators == std::vector<std::string>({"Zeldin", "Uther", "Richards", "Banks"}));

    TEST_ASSERT(activities.at(17).Name == "SLA451");
    TEST_ASSERT(activities.at(17).Section == "B");
    TEST_ASSERT(activities.at(17).ExpectedEnrollment == 100);
    TEST_ASSERT(activities.at(16).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer", "Shaw"}));
    TEST_ASSERT(activities.at(16).OtherFacilitators == std::vector<std::string>({"Zeldin", "Uther", "Richards", "Banks"}));


}

void test_Config_ParseRooms()
{

    std::vector<Room> rooms = ParseRooms("./config/rooms.json");

    // Assertions for Slater 003
    TEST_ASSERT(rooms.at(0).Name == "Slater");
    TEST_ASSERT(rooms.at(0).Number == 3);
    TEST_ASSERT(rooms.at(0).Capacity == 45);

    // Assertions for Roman 216
    TEST_ASSERT(rooms.at(1).Name == "Roman");
    TEST_ASSERT(rooms.at(1).Number == 216);
    TEST_ASSERT(rooms.at(1).Capacity == 30);

    // Assertions for Loft 206
    TEST_ASSERT(rooms.at(2).Name == "Loft");
    TEST_ASSERT(rooms.at(2).Number == 206);
    TEST_ASSERT(rooms.at(2).Capacity == 75);

    // Assertions for Roman 201
    TEST_ASSERT(rooms.at(3).Name == "Roman");
    TEST_ASSERT(rooms.at(3).Number == 201);
    TEST_ASSERT(rooms.at(3).Capacity == 50);

    // Assertions for Loft 310
    TEST_ASSERT(rooms.at(4).Name == "Loft");
    TEST_ASSERT(rooms.at(4).Number == 310);
    TEST_ASSERT(rooms.at(4).Capacity == 108);

    // Assertions for Beach 201
    TEST_ASSERT(rooms.at(5).Name == "Beach");
    TEST_ASSERT(rooms.at(5).Number == 201);
    TEST_ASSERT(rooms.at(5).Capacity == 60);

    // Assertions for Beach 301
    TEST_ASSERT(rooms.at(6).Name == "Beach");
    TEST_ASSERT(rooms.at(6).Number == 301);
    TEST_ASSERT(rooms.at(6).Capacity == 75);

    // Assertions for Logos 325
    TEST_ASSERT(rooms.at(7).Name == "Logos");
    TEST_ASSERT(rooms.at(7).Number == 325);
    TEST_ASSERT(rooms.at(7).Capacity == 450);

    // Assertions for Frank 119
    TEST_ASSERT(rooms.at(8).Name == "Frank");
    TEST_ASSERT(rooms.at(8).Number == 119);
    TEST_ASSERT(rooms.at(8).Capacity == 60);


}

void test_Config_ParseTimes()
{
    std::vector<double> times = ParseTimes("./config/times.json");

    TEST_ASSERT(times == std::vector<double>({10, 11, 12, 13, 14, 15}));
}