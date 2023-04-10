
#include "acutest.h"

#include "Config.test.h"

TEST_LIST = {
   { "ParseActivities", test_Config_ParseActivities },
   { "ParseRooms", test_Config_ParseRooms },
   { "ParseTimes", test_Config_ParseTimes },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};