
#include "acutest.h"

#include "Config.test.h"
#include "GA.test.h"

TEST_LIST = {
   { "ParseActivities", test_Config_ParseActivities },
   { "ParseRooms", test_Config_ParseRooms },
   { "ParseTimes", test_Config_ParseTimes },
   { "Softmax", test_GA_Softmax },
   { NULL, NULL }     /* zeroed record marking the end of the list */
};