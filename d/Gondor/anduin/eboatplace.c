/*
 * anduin/eboatplace.c
 */
#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "river");

void
create_room()
{
    rivertype = "broad river";
    landname = "Ithilien";
    rivername = "Anduin";
    cur_dir = "southeast";
    up_dir = "north";
    shore = ({"east"});
    cur_str = 40;
    add_exit(ITH_DIR + "osgiliath/boatplace", "southeast", "@@do_swim", 4);
    add_exit(ANDUIN_DIR + "eosg2bank", "north", "@@do_swim", 9);
    add_exit(ITH_DIR + "osgiliath/boatplace", "east", "@@do_swim", 5);
    make_the_room();
}

