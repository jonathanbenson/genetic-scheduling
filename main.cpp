
#include <iostream>
#include "Config.h"

int main()
{

    Config config;

    config.ParseActivities("./config/activities.json");

    return 0;
}