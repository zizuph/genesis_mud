#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are in a cold, stone hallway. The walls are decorated "+
    "with tapestries and torches. To the west, you see a stairwell.\n");
    add_item("tapestries","They depict dragons, priests, warriors and "+
    "all sorts of neat stuff.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("stairwell","It is to your west, and it goes up.\n");
    add_exit(KEEP_DIR + "keep06","west",0);
    add_exit(KEEP_DIR + "keep04","east",0);
}

