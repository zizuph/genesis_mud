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
    add_my_desc("The Vale spreads out in all directions. The Misty " +
        "Mountains loom in the distance to the west and a Mirkwood " +
        "forest to the east.\n");

    set_add_misty_near();
    set_add_mirk_near();
    set_add_wildlife();
    set_add_river_close();

    add_exit(WEST_DIR + "p1n5", "east");
    add_exit(WEST_DIR + "p2n4", "south");
 
}
