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
    set_areaname("third ring");
    set_areadesc("street");
    set_vbfc_extra(road_desc5);

    add_my_desc("An important avenue intersects here, running east " +
        "into Thalandrone. The Third Ring continues north and " +
        "south.\n");

    add_exit(RD3_DIR + "rd32",     "north");
    add_exit(RD3_DIR + "rd30",     "south", "@@block_road@@");
    add_exit(OTHERS_DIR + "av11",  "east");

}
/*
int
block_rd()
{
    if (this_player()->query_wiz_level()) return 0;

        write("A spell has been cast here, preventing " +
            "visitors to go that way.\n");
    return 1;
}
*/
