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
    set_vbfc_extra(road_desc1);
    add_my_desc("The land is a healthy green from the marshy land.\n");
    
    set_add_river_close();
    set_add_misty_near();
    reset_shire_room();

    add_exit(WEST_DIR + "rd03", "west");
    add_exit(WEST_DIR + "rd01", "east");
 
}

void reset_shire_room()
{
}
