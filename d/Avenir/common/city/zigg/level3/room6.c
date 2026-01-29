// Ziggurat galleria (room6.c)
// creator(s):   Zielia 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_ROOM3;

public void
zig_room(void)
{
    set_short("southern galleria, north of an archway");
    set_long("You are walking in the galleria of the Ziggurat. "+
	"Glossy black stone surrounds you with an opening to the south. "+
	"To the north you can see a black rail that "+
	"surrounds the overlook to the plaza below and the "+
	"@@see_tree@@.@@see_nearby@@\n");

    add_exit("room5", "east", 0);
    add_exit("room7", "west", 0);
    add_exit("garden", "south", 0);

    add_item(({"archway"}), "The archway to the south leads out "+
	"to the terraced garden of the Ziggurat.\n");
}
