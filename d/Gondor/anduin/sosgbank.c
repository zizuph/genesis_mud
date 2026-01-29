/*
 * anduin/sosgbank.c
 */
#include "/d/Gondor/defs.h"
inherit (LIB_DIR + "river");

void
create_room()
{
    rivertype = "broad river";
    landname = "Anorien";
    rivername = "Anduin";
    cur_dir = "southwest";
    up_dir = "north";
    shore = ({"west"});
    cur_str = 40;
    add_exit(OSG_DIR + "wbank1", "southwest", "@@do_swim", 4);
    add_exit(ANDUIN_DIR + "wboatplace", "north", "@@do_swim", 9);
    add_exit(OSG_DIR + "wbank1", "west", "@@do_swim", 5);
    make_the_room();
}

