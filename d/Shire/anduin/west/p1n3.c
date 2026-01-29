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
    set_vbfc_extra(vale_desc1);

    add_my_desc("Many green plants grow here, fed by the river nearby.\n");

    set_add_all_rooms();

    set_add_misty_near();
    set_add_mirk_near();
    set_add_wildlife();
    set_add_river_close();
    reset_shire_room();

    add_exit(WEST_DIR + "p1n4", "north");
    add_exit(WEST_DIR + "p1n2", "south");
    add_exit(WEST_DIR + "wbn3", "east");
    add_exit(WEST_DIR + "p2n3", "west");
 
}

void reset_shire_room()
{
}
