#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are in a long hallway T intersection. The air is "+
    "warm and sweet smelling here. The corridor leads west to another "+
    "corner of the keep, south into a well-lit, sweet smelling room, "+
    "while to the east is a stairwell.\n");
    add_item("tapestries","Pictures of dragons, soldiers, knights "+
    "crosses, and all kinds of cool stuff.\n");
    add_item("stairwell","Its to your east.\n");
    add_item("torches","They light the dim corridor.\n");
    add_exit(KEEP_DIR + "keep10","east",0);
    add_exit(KEEP_DIR + "keep12","west",0);
    add_exit(KEEP_DIR + "keep08","south",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard_s", 4);
}

