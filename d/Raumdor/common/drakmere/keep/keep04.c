#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are at a corner between two hallways that lead north "+
    "and west. There is a little window facing out into the courtyard "+
    "here, and you feel peaceful.\n");
    add_item("window","You see the beautiful green courtyard outside "+
    "with all its colorful and sweet smelling flowers.\n");
    add_exit(KEEP_DIR + "keep05","west",0);
    add_exit(KEEP_DIR + "keep01","north",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard_s", 4);
}

