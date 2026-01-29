#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are in a stone corridor. The air smells good here, "+
    "and the good scent seems to be coming from the room off to your "+
    "east. The corridor continues to the north and south.\n");
    add_item("tapestries","They depict dragons, priests, warriors and "+
    "all sorts of neat stuff.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("stairwell","It is to your west, and it goes up.\n");
    add_exit(KEEP_DIR + "keep03","south",0);
    add_exit(KEEP_DIR + "keep08","east",0);
    add_exit(KEEP_DIR + "keep12","north",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard_s", 4);
}

