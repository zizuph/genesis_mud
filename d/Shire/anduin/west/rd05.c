/*
 * Road in western vales of Anduin.
 * By Finwe, June 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit VALE_BASE;



void
create_vale_room()
{
    set_area("on the western edge of");
    set_areaname("the Old Forest Road");
    set_land("the Vales of the Anduin");
    set_vbfc_extra(road_desc4);
    add_my_desc("It runs through some hills. Some tall grass " +
        "and flowers grow alongside the path.\n");
    
    set_add_river_far();
    set_add_misty_close();
    reset_shire_room();

    add_exit(WEST_DIR + "rd06", "northwest");
    add_exit(WEST_DIR + "rd04", "east");
 
}

void reset_shire_room()
{
}
