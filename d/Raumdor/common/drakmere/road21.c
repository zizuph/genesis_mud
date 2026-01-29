#include "defs.h"
inherit ROAD_ROOM;
/* By Sarr */

void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On a dirt road in Drakmere");
    set_long("You are on a dirt road in the east part of the city of "+
    "Drakmere. To the west, the city center lies, while to the east, "+
    "the road ends at the great stone wall. The road branches off north "+
    "and south from here, where it runs along the wall.\n");
    add_item("wall","The great wall that surrounds the entire city "+
    "to protect it from the savages that lurk outside.\n");
    reset_room();
    add_exit(DRAKMERE_DIR + "road20","west",0,0,0);
    add_exit(DRAKMERE_DIR + "road39","north",0,0,0);
    add_exit(DRAKMERE_DIR + "road40","south",0,0,0);
    
    add_npc(DRAKMERE_NPC_DIR + "dguard", 2);
}

void
reset_room()
{
   
}

