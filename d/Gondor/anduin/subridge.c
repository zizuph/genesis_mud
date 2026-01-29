/*
 * anduin/subridge.c
 */
#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "river");

void
create_room()
{
    rivertype = "broad river";
    landname = "Anorien";
    rivername = "Anduin";
    cur_dir = "south";
    up_dir = "north";
    shore = ({"west"});
    cur_str = 45;
    extraline = "A small platform or pier has been built out into the river " +
        "under the stone bridge to the north. ";
    add_exit(ANDUIN_DIR + "wosg4bank", "south", "@@do_swim", 4);
    add_exit(OSG_DIR + "underbridge", "north", "@@do_swim", 9);
    add_exit(OSG_DIR + "wosg3", "west", "@@do_swim", 5);
    make_the_room();
}

