
#include "acutest.h"

#include "Config.h"

void test_Config_ParseActivities(void)
{
    Config config;

    config.ParseActivities("./config/activities.json");

    std::vector<Activity> activities = config.GetActivities();

    // Assertions for SLA100
    TEST_ASSERT(activities.at(0).Name == "SLA100");
    TEST_ASSERT(activities.at(0).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(0).PreferredFacilitators == std::vector<std::string>({"Glen", "Lock", "Banks", "Zeldin"}));
    TEST_ASSERT(activities.at(0).OtherFacilitators == std::vector<std::string>({"Numen", "Richards"}));

    // Assertions for SLA191
    TEST_ASSERT(activities.at(1).Name == "SLA191");
    TEST_ASSERT(activities.at(1).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(1).PreferredFacilitators == std::vector<std::string>({"Glen", "Lock", "Banks", "Zeldin"}));
    TEST_ASSERT(activities.at(1).OtherFacilitators == std::vector<std::string>({"Numen", "Richards"}));

    // Assertions for SLA201
    TEST_ASSERT(activities.at(2).Name == "SLA201");
    TEST_ASSERT(activities.at(2).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(2).PreferredFacilitators == std::vector<std::string>({"Glen", "Banks", "Zeldin", "Shaw"}));
    TEST_ASSERT(activities.at(2).OtherFacilitators == std::vector<std::string>({"Numen", "Richards", "Singer"}));

    // Assertions for SLA291
    TEST_ASSERT(activities.at(3).Name == "SLA291");
    TEST_ASSERT(activities.at(3).ExpectedEnrollment == 50);
    TEST_ASSERT(activities.at(3).PreferredFacilitators == std::vector<std::string>({"Lock", "Banks", "Zeldin", "Singer"}));
    TEST_ASSERT(activities.at(3).OtherFacilitators == std::vector<std::string>({"Numen", "Richards", "Shaw", "Tyler"}));

    // Assertions for SLA303
    TEST_ASSERT(activities.at(4).Name == "SLA303");
    TEST_ASSERT(activities.at(4).ExpectedEnrollment == 60);
    TEST_ASSERT(activities.at(4).PreferredFacilitators == std::vector<std::string>({"Glen", "Zeldin", "Banks"}));
    TEST_ASSERT(activities.at(4).OtherFacilitators == std::vector<std::string>({"Numen", "Singer", "Shaw"}));

    // Assertions for SLA304
    TEST_ASSERT(activities.at(5).Name == "SLA304");
    TEST_ASSERT(activities.at(5).ExpectedEnrollment == 25);
    TEST_ASSERT(activities.at(5).PreferredFacilitators == std::vector<std::string>({"Glen", "Banks", "Tyler"}));
    TEST_ASSERT(activities.at(5).OtherFacilitators == std::vector<std::string>({"Numen", "Singer", "Shaw", "Richards", "Uther", "Zeldin"}));

    // Assertions for SLA394
    TEST_ASSERT(activities.at(6).Name == "SLA394");
    TEST_ASSERT(activities.at(6).ExpectedEnrollment == 20);
    TEST_ASSERT(activities.at(6).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer"}));
    TEST_ASSERT(activities.at(6).OtherFacilitators == std::vector<std::string>({"Richards", "Zeldin"}));

    // Assertions for SLA449
    TEST_ASSERT(activities.at(7).Name == "SLA449");
    TEST_ASSERT(activities.at(7).ExpectedEnrollment == 60);
    TEST_ASSERT(activities.at(7).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer", "Shaw"}));
    TEST_ASSERT(activities.at(7).OtherFacilitators == std::vector<std::string>({"Zeldin", "Uther"}));

    // Assertions for SLA451
    TEST_ASSERT(activities.at(8).Name == "SLA451");
    TEST_ASSERT(activities.at(8).ExpectedEnrollment == 100);
    TEST_ASSERT(activities.at(8).PreferredFacilitators == std::vector<std::string>({"Tyler", "Singer", "Shaw"}));
    TEST_ASSERT(activities.at(8).OtherFacilitators == std::vector<std::string>({"Zeldin", "Uther", "Richards", "Banks"}));

}

