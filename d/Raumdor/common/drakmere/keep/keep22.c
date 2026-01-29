#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */


void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are now in the middle of a stairwell. The staircase "+
    "here spirals upwards to the upper keep towers, and back down to the "+
    "lower level of the keep. The way branches to the east into the "+
    "second level of the keep.\n");
    add_item("torches","They light up this dim place.\n");
    add_item("stairwells","It leads up or down.\n");
    add_exit(KEEP_DIR + "keep27","up",0);
    add_exit(KEEP_DIR + "keep06","down",0);
    add_exit(KEEP_DIR + "keep23","east",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard", 4);
}
