// Ziggurat galleria (room4.c)
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
    set_short("eastern galleria");
    set_long("You are walking in the galleria of the Ziggurat. "+
	"Glossy black stone surrounds you except to the north and "+
	"south where you may continue walking. "+
	"To the west you can see a black rail that "+
	"surrounds the overlook to the plaza below and the "+
	"@@see_tree@@.@@see_nearby@@\n");

    add_exit("room3", "north",  0);
    add_exit("room5", "south",  0);
}
