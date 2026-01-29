#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are at a T intersection in the upper level of the "+
    "Keep of Drakmere. The torch lined corridor heads north deeper "+
    "into the keep, while east and west, are stairwells.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("stairwells","To the east and west.\n");
    add_exit(KEEP_DIR + "keep20","north",0);
    add_exit(KEEP_DIR + "keep24","east",0);
    add_exit(KEEP_DIR + "keep22","west",0);

    add_npc(DRAKMERE_NPC_DIR + "eg_guard", 3);
}

