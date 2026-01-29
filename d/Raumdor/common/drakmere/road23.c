#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on dirt road that heads north through a large "+
    "grassy field. There air here smells fresh and clean, as flowers "+
    "pop out of the ground along the fields, perfuming the air. Off "+
    "in the distance to the south, you see a large stone keep, while "+
    "to the north you see the corner where the north and west stone "+
    "walls that protect the city meet.\n");
    add_item(({"grassy field","field"}),"A beautiful green field of "+
    "grass and flowers. You see children playing around.\n");
    add_item("keep","Probably where the Lord of Drakmere and his followers "+
    "could be found.\n");
    add_item("flowers","Red, purple, blue, and yellow flowers dot the "+
    "entire area.\n");
    add_item("children","They are playing around among the flowers and "+
    "beautiful green grass hills.\n");
    add_item(({"walls","stone walls"}),"They protect the city from the "+
    "savages that lay waiting outside in the darkness. You see a few "+
    "guards walking around the tops, patroling.\n");
    add_exit(DRAKMERE_DIR + "road13","south",0,0,0);
    add_exit(DRAKMERE_DIR + "road24","north",0,0,0);
    
    add_npc(DRAKMERE_NPC_DIR + "dguard", 2);
}
