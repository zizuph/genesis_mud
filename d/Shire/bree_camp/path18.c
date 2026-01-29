/*
 * Path in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"

inherit CAMP_BASE;
inherit ENTER_BASE;

void
create_camp_room()
{
    set_extraline("Tents line the paths of the camp. They are of " +
        "varying sizes and descriptions. They provide shelter " +
        "for the inhabitants of the camp and ready places to " +
        "store their loot from raids. The paths are well worn " +
        "that run throughout the camp.");

    add_exit(CAMP_DIR + "path13", "north");
    add_exit(CAMP_DIR + "path22", "south");
    add_exit(CAMP_DIR + "path19", "east");
    add_exit(CAMP_DIR + "path17", "west");

    set_tent_name("tent18");
    reset_shire_room();
}

