/*
 * Road in eastern vales of Anduin.
 * By Finwe, June 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit VALE_BASE;

void
create_vale_room()
{
    set_area("on the eastern edge of");
    set_areaname("the Old Forest Road");
    set_land("the Vales of the Anduin");

    set_vbfc_extra(road_desc1);
    add_my_desc("The bushes are large this close to the ford.\n");
    
    set_add_river_close();
    set_add_misty_near();

    add_exit(EAST_DIR + "eford", "west");
    add_exit(EAST_DIR + "rd02", "east");

 
}
