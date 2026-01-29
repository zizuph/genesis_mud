#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */


void reset_room();

void
create_room()
{
    ::create_room();
    set_short("On the towers of the Keep of Drakmere");
    set_long("You are now standing on the top of the southwest tower "+
    "of the Keep of Drakmere. All around you, you see the city of "+
    "Drakmere, plus over the walls surrounding it, the countryside. "+
    "It is a breathtaking sight.\n");
    add_exit(KEEP_DIR + "keep22","down",0);
    
    add_npc(DRAKMERE_NPC_DIR + "eg_guard_s", 4);
    
    reset_room();
}

void
reset_room()
{

}

