/*
 * anduin/suebridge.c
 */
#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "river");

void
create_room()
{
    rivertype = "broad river";
    landname = "Ithilien";
    rivername = "Anduin";
    cur_dir = "south";
    up_dir = "north";
    shore = ({"east"});
    cur_str = 45;
    extraline = "A small platform or pier has been built out into the river " +
        "under the stone bridge to the north. ";
    add_exit(ANDUIN_DIR + "eosg1bank", "south", "@@do_swim", 4);
    add_exit(ITH_DIR + "osgiliath/underbridge", "north", "@@do_swim", 9);
    add_exit(ITH_DIR + "osgiliath/bank", "east", "@@do_swim", 5);
    make_the_room();
}

