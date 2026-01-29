#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */


void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are now in the middle of a stairwell. The staircase "+
    "here spirals upwards to the upper keep tower. The way to the east "+
    "leads you back into the corridor through the upper level.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("stairwells","It leads up.\n");
    add_exit(KEEP_DIR + "keep25","up",0);
    add_exit(KEEP_DIR + "keep14","east",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard", 4);
}
