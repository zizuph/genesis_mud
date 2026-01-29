#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are at a T intersection in the upper level of the "+
    "Keep of Drakmere. The torch lined corridor heads south deeper "+
    "into the keep, while east and west, are stairwells.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("stairwells","To the east and west.\n");
    add_exit(KEEP_DIR + "keep17","south",0);
    add_exit(KEEP_DIR + "keep13","east",0);
    add_exit(KEEP_DIR + "keep15","west",0);

    add_npc(DRAKMERE_NPC_DIR + "eg_guard", 4);
}

