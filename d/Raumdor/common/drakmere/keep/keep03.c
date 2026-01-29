#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are in a long hallway T intersection. The air is "+
    "stale here. You hear humming coming from the chamber to the east, "+
    "while to the south is a stairwell, and to the north the hallway "+
    "continues. Torches and tapestries line the walls here.\n");
    add_item("tapestries","Pictures of dragons, soldiers, knights "+
    "crosses, and all kinds of cool stuff.\n");
    add_item("stairwell","Its to your south.\n");
    add_item("torches","They light the dim corridor.\n");
    add_exit(KEEP_DIR + "keep02","east",0);
    add_exit(KEEP_DIR + "keep09","north",0);
    add_exit(KEEP_DIR + "keep06","south",0);
}

