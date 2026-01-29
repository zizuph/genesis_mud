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
    set_vbfc_extra(road_desc5);
    add_my_desc("Some trees grow on both sides of the path.\n");
    add_item(({"trees", "solitary stand of trees",
            "stand of trees"}),
        "The trees are evergreeens, growing on both sides of " +
        "the road. The @@light_type@@ filters through its " +
        "branches.\n");
    
    set_add_river_near();
    set_add_misty_far();

    add_exit(EAST_DIR + "rd02", "west");
    add_exit(EAST_DIR + "rd04", "east");
 
}
