/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

//inherit GATE_BASE;
inherit ROAD_BASE;
 
void
create_road_room()
{

    set_areadesc("large gate");
    set_area("outside");
    set_areaname("Bree");
    set_land("Eriador");

    add_my_desc("This is the northern most part of Bree, protected " +
        "by a the North Gate. A lonely road leads west towards " +
        "Deadman's Dike and southeast into Bree. A tall hedge grows " +
        "along the outside of the village, surrounded by a deep dike.\n");
    add_item(({"gate", "gates"}), "@@my_gates");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    add_item(({"gate", "north gate"}),
        "The North Gate is sturdy and made of thick timbers. It " +
        "swings inward, allowing people to enter or leave the town.\n");

    set_add_dike();
    set_add_outside_hedge();

    add_exit(ROAD_DIR + "road03",   "west");
    add_exit(ROAD_DIR + "broad23",  "southeast", "@@block@@");
    add_exit(ROAD_DIR + "nhedge07", "east");
    add_exit(ROAD_DIR + "nhedge06", "south");

  gatestate = 1;
    
}


init()
{
    ::init();
    add_action("knock", "knock");
    check_gates();
}

