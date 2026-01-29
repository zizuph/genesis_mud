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
    set_vbfc_extra(road_desc2);
    add_my_desc("Some trees grow here in a solitary stand on " +
        "either side of the path.\n");
    add_item(({"trees", "solitary stand of trees",
            "stand of trees"}),
        "The trees are evergreeens, growing on either side of " +
        "the road. They offer shade from the @@light_type@@, " +
        "which filters through its branches.\n");
    
    set_add_river_near();
    set_add_misty_near();
    reset_shire_room();

    add_exit(WEST_DIR + "rd05", "west");
    add_exit(WEST_DIR + "rd03", "east");
 
}

void reset_shire_room()
{
}
