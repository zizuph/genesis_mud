#include "defs.h"
inherit KEEP_ROOM;
/* The Drakmere Keep, by Sarr */

object cook;
void reset_room();

void
create_room()
{
    ::create_room();
    
    set_short("Inside the Keep of Drakmere");
    set_long("You are now inside the kitchen of the keep. There are "+
    "pots and pans everywhere. Large fire stoves burn along the walls. "+
    "The smells from the cooking food are wonderful. Your mouth waters "+
    "as you inhale the delicious scent.\n");
    add_item(({"pots","pans"}),"They are lined on the walls, on the "+
    "various counters and tables, and on the bruning stoves.\n");
    add_item("stoves","They burn brightly, cooking the food within.\n");
    add_exit(KEEP_DIR + "keep09","west",0);
    add_exit(KEEP_DIR + "keep11","north",0);
    clone_object(KEEP_DIR + "kstuff")->move(TO);
    clone_object(KEEP_DIR + "kstuff2")->move(TO);
    reset_room();
}

void
reset_room()
{
    if(!cook)
    {
        cook = clone_object(DRAKMERE_NPC_DIR + "k_cook");

        cook->move_living("xxx",TO);
    }
}

