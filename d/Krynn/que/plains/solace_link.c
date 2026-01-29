#include "local.h"
inherit "/d/Krynn/std/outside_room";

int block()
{
    this_player()->catch_tell("Temporaly closed...\n");
    return 1;
}

void
create_krynn_room()
{
    set_short("The Plains");
    set_long("You are standing in the grassy plains east of Solace. " +
	     "West of you is a pleasant looking meadow. Towards your " +
	     "east, a track known as the Sageway continues onto the plains, " +
	     "west you will soon reach the village of Solace.\n");
    
//    add_exit("", "east", block);
    add_exit(TDIR+"rooms/plain-3-10-1", "east");
    add_exit(SOLACE_VILLAGE, "west");
}
