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

    add_my_desc("This "+areadesc+", known as the Northwest Avenue, " +
        "runs northwest and southeast through Thalandrone. It " +
        "provides a direct route to the Palace and the forest. " +
        "To the west is a stately building. \n");
   add_item("stately building",
        "The stately build is one story and fashioned of white " +
        "stone. It is surrounded by gardens and nearly hidden by " +
        "ancient trees.\n");

    add_exit(RD3_DIR + "rd37",  "northwest");
    add_exit(RD2_DIR + "rd23",  "southeast");

}

int
block_rd()
{
    if (this_player()->query_wiz_level()) return 0;

        write("A spell has been cast here, preventing " +
            "visitors to go that way.\n");
    return 1;
}

