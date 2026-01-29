#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("The dirt road ends here at the corner of the north "+
    "and east stone walls. The road leads west and south through the "+
    "residential area.\n");
    add_item(({"walls","stone walls"}),"They protect the city from the "+
    "savages that lay waiting outside in the darkness. You see a few "+
    "guards walking around the tops, patroling.\n");
    reset_room();
    add_exit(DRAKMERE_DIR + "road34","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road36","south",0,0,0);

    add_npc(DRAKMERE_NPC_DIR + "dguard", 3);
}


