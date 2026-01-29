#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */


void reset_room();

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are at the intersection of the north and west "+
    "corridors. A spiral staircase leads up from here into the "+
    "upper part of the keep. There are torches on the walls, lighting "+
    "up this grim stone area.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("staircase","It goes up to the next level of this Keep.\n");
    add_exit(KEEP_DIR + "keep03","north",0);
    add_exit(KEEP_DIR + "keep05","east",0);
    add_exit(KEEP_DIR + "keep22","up",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard_s", 4);
    
    reset_room();
}

void
reset_room()
{

}

