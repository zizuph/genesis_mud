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
    set_vbfc_extra(vale_desc3);

    add_my_desc("The mountains are close by, rising to the west.\n");

    set_add_all_rooms();

    set_add_misty_close();
    set_add_mirk_far();
    set_add_wildlife();
    set_add_river_near();
    reset_shire_room();

    add_exit(WEST_DIR + "p2n5", "north");
    add_exit(WEST_DIR + "p2n3", "south");
    add_exit(WEST_DIR + "p1h4", "east");
    add_exit(WEST_DIR + "p3n4", "west");
 
}

void reset_shire_room()
{
}
