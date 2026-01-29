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
    "sorts also decorate the wall. The hallway leads south and east "+
    "deeper into this stone keep, while north is the exit to outside.\n");
    add_item("tapestries","Pictures of dragons, soldiers, knights "+
    "crosses, and all kinds of cool stuff.\n");
    add_item("torches","They light the dim corridor.\n");
    add_exit(KEEP_DIR + "keep11","east",0);
    add_exit(DRAKMERE_DIR + "road22","north","@@msg");
    add_exit(KEEP_DIR + "keep09","south",0);
}

int
msg()
{
    write("You step outside into the fresh air.\n");
    return 0;
}

