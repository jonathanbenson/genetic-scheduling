
#include "acutest.h"

#include "Config.test.h"

TEST_LIST = {
   { "Config::ParseActivities", test_Config_ParseActivities },
   { "Config::ParseRooms", test_Config_ParseRooms },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};