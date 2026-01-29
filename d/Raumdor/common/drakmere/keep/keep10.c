#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

object guard;
void reset_room();

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are at the intersection of the south and east "+
    "corridors. A spiral staircase leads up from here into the "+
    "upper part of the keep. There are torches on the walls, lighting "+
    "up this grim stone area.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("staircase","It goes up to the next level of this Keep.\n");
    add_exit(KEEP_DIR + "keep07","south",0);
    add_exit(KEEP_DIR + "keep11","west",0);
    add_exit(KEEP_DIR + "keep13","up",0);
    reset_room();
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(DRAKMERE_NPC_DIR + "eg_guard");

        guard->move_living("xxx",TO);
    }
}

