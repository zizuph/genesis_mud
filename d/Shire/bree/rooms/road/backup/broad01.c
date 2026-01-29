/*
 * Road in Bree
 * By Finwe, June  2001
 *
 * Gates fixed 2010/07/25 Lavellan
 *
 * 2011/07/21 Lavellan - Changed to use stdgateroom, commented out redundant
 *                       stuff here
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"

//inherit ROAD_BASE;
inherit "/d/Shire/bree/stdgateroom.c";

object human;
//int gatestate;  /* 0 = closed, 1 = open */

string
gate_desc()
{
    string str;
    if (gatestate) str = "The gates are open. ";
    else str = "The gates are closed to keep villains out. ";
    return str + "The Great East Road runs west towards the western gate " +
        "and east into Bree.\n";
}

void
create_gateroom()
{
    set_areadesc("busy road");
    set_area("inside the");
    set_areaname("West Gate");
    set_land("Bree");
    set_vbfc_extra(gate_desc);

    add_item(({"west gate", "gate", "city gate"}),
        "@@my_gates@@");
    add_item("timbers",
        "The timbers are used in gate construction. They are " +
        "tall and smooth,\n");
    add_item(({"bands", "iron bands"}),
        "The iron bands are thick and hold the timbers together " +
        "in the city gates.\n");

    set_add_ger();
    set_other_room(ROAD_DIR + "wgate");
    set_direction("west");

    add_exit(ROAD_DIR + "broad02", "east");
}

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(human))
    {
        human = clone_object(NPC_DIR + "human");
        human->move(TO);
        human->set_restrain_path("/d/Shire/bree");
        human->set_random_move(2);

    }
}
