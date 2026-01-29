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
    set_short("Outside Gateway");
    set_long("You are standing just outside the village of Gateway. " +
	     "Towards your east, a track continues into the wilderness, " +
	     "west is the small village of Gateway.\n");
    
//    add_exit("", "east", block);
    add_exit(TDIR+"rooms/plain-2-17-1", "east");
    add_exit(GATEWAY_VILLAGE, "west");
}
