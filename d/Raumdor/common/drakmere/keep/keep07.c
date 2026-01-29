#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are walking along a hallway lined with torches and "+
    "tapestries. The air is cold and damp here, but you smell sweet "+
    "fragrances coming from garden outside the window to your east.\n");
    add_item("window","You see the courtyard's beautiful garden with "+
    "all its colorful flowers.\n");
    add_item("tapestries","Pictures of dragons, soldiers, knights "+
    "crosses, and all kinds of cool stuff.\n");
    add_item("torches","They light the dim corridor.\n");
    add_exit(KEEP_DIR + "keep10","north",0);
    add_exit(KEEP_DIR + "keep01","south",0);
}

