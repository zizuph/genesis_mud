#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */


void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You inside a corridor within the upper level of the "+
    "Keep of Drakmere. The walls around you are lighted by the dim "+
    "torchlight coming from the torches. The way leads west into what "+
    "looks like a huge reception chamber, and north and south along the "+
    "corridor.\n");
    add_item("torches","They light up this dim place.\n");
    add_exit(KEEP_DIR + "keep23","south",0);
    add_exit(KEEP_DIR + "keep17","north",0);
    add_exit(KEEP_DIR + "keep21","west",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard", 4);
}
