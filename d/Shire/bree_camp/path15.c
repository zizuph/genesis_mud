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

    add_exit(CAMP_DIR + "path10", "north");
    add_exit(CAMP_DIR + "path16", "east");
    add_exit(CAMP_DIR + "path20", "southeast");

    set_tent_name("tent15");
    reset_shire_room();
}

void reset_shire_room()
{
    clone_camp_orcs();
}
