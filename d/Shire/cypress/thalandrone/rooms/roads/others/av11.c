/*
 * Road in Third Ring of Thalandor
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "/d/Shire/cypress/sys/defs.h" 
#include "local.h"

//inherit "/d/Shire/cypress/thalandrone/base_road.c";
inherit ROAD_BASE;
 
void
create_road_room()
{

    set_areadesc("avenue");
    set_areaname("between the second and third ring");
    set_vbfc_extra(road_desc3);

    add_my_desc("This "+areadesc+", known as the West Avenue, " +
        "runs east and west through Thalandrone. It provides a " +
        "direct route to the Palace. \n");

    add_exit(RD3_DIR + "rd31",  "west");
    add_exit(RD2_DIR + "rd19",  "east");

}

int
block_rd()
{
    if (this_player()->query_wiz_level()) return 0;

        write("A spell has been cast here, preventing " +
            "visitors to go that way.\n");
    return 1;
}

