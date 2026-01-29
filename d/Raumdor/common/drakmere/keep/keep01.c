#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are now inside the stone keep of Drakmere. The walls "+
    "around hold torches that light the dim area. Tapestries of all "+
    "sorts also decorate the wall. The hallway leads west into some "+
    "sort of large chamber, while another hallway leads north and "+
    "south into other parts of the keep.\n");
    add_item("tapestries","Pictures of dragons, soldiers, knights "+
    "crosses, and all kinds of cool stuff.\n");
    add_item("torches","They light the dim corridor.\n");
    add_exit(DRAKMERE_DIR + "road49","east",0);
    add_exit(KEEP_DIR + "keep02","west",0);
    add_exit(KEEP_DIR + "keep07","north",0);
    add_exit(KEEP_DIR + "keep04","south",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard_s", 4);
}

