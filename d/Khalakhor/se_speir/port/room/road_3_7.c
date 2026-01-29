/*
 * This is part of a road in Port Macdunn.
 *
 * Khail/Zima - July 25/97
 * Zima       - June 19/98 - made gate usable
 */
#pragma strict_types
 
#include "room.h"
#include "/d/Khalakhor/guilds/sean-rhian/lib/zdoor.h"
#define  IPATH  KIRK_ROOM+"kgarden1"
inherit  ZOUTDOOR;
inherit  ROADBASE;
 
public string
query_dir_to_jail()
{
    return "east";
}
 
public void
create_road()
{
    set_short("end of a wide dirt road");
    set_long("   You are at end of the wide dirt road in the village "+
        "of port MacDunn. A long stone hall with a thatched roof "+
        "extends along the road on its south side, while a garden "+
        "guarded by a high iron fence runs along to the north. There "+
        "is a gate here to the garden in the fence. To the west, " +
        "the western embankment rises at the edge of the village, "+
        "preventing further progress in that direction.\n");
 
    add_item("hall",
        "It is a long stone hall, typical of the buildings of the "+
        "village, with stone walls and a thatched roof. It extends "+
        "along the road on its southern side.\n");
    add_item("garden",
        "It is a lush green garden growing on the west side of the "+
        "large stone building. It is guarded by a high iron fence, "+
        "in which there is a gate here.\n");
    add_item("fence",
        "Made of tall iron spikes set into the ground and joined by "+
        "thick horizontal bars, it runs along the north side of the "+
        "road here, protecting the garden on the other side. There is "+
        "a gate through the fence here.\n");
 
    add_exit(ROOM + "road_4_7", "east");
 
    setup_outdoor("north", IPATH, ({"gate"}),
        "Made the same as the fence, the gate is an entrance into the "+
        "garden from the road.",
        "ivy-covered gate", 0);
}
 
void init()
{
   ::init();
   add_outdoor_actions();
}
