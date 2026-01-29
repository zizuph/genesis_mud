/*
 * anduin/eosg2bank.c
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
    cur_str = 40;
    extraline = "The stone bridge of Osgiliath is further north up the river. ";
    add_exit(ANDUIN_DIR + "eboatplace", "south", "@@do_swim", 4);
    add_exit(ANDUIN_DIR + "eosg1bank", "north", "@@do_swim", 9);
    add_exit(ITH_DIR + "osgiliath/bank2", "east", "@@do_swim", 5);
    make_the_room();
}

