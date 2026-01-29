/*
 * Path in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"

inherit CAMP_BASE;

void
create_camp_room()
{
    set_extraline("This is the entrance to a orc camp. A wide " +
        "path leads north into the camp. Standards line the " +
        "path, warning anyone to beware. Tents can be seen in " +
        "the distance of various sizes.");

    add_exit(CAMP_DIR + "path21", "north");
    add_exit(CAMP_DIR + "path24", "south");

    reset_shire_room();
}


void reset_shire_room()
{
    clone_camp_orcs();
}
