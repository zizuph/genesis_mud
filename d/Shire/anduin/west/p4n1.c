/*
 * Vale in the Vales of Anduin
 * By Finwe, January 2003
 */
 
#pragma strict_types
 
#include "local.h"

inherit VALE_BASE;

void
create_vale_room()
{
    set_area("meadow in");
    set_areaname("the Vales");
    set_land("the Anduin");
    set_areatype(0);
    set_areadesc("lush");
    set_vbfc_extra(vale_desc2);

    add_my_desc("Bushes and trees grow in small clusters about the area.\n");

    set_add_all_rooms();

    set_add_misty_close();
    set_add_mirk_far();
    set_add_wildlife();
    set_add_river_far();

    add_exit(WEST_DIR + "p4n2", "north");
    add_exit(WEST_DIR + "rd04", "south");
    add_exit(WEST_DIR + "p3n1", "east");
    add_exit(WEST_DIR + "p5n1", "west");
 
}
