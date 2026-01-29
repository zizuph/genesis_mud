// Ziggurat galleria (room3.c)
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
    set_short("northeast galleria, between a shop and the post");
    set_long("You are walking in the galleria of the Ziggurat. "+
	"Glossy black stone surrounds you with openings to the north "+
	"and the west. To the southwest you can see a black rail that "+
	"surrounds the overlook to the plaza below and the "+
	"@@see_tree@@.@@see_nearby@@\n");

    add_exit("room2", "west",  0);
    add_exit("room4", "south", 0);

    add_exit("post",   "north", 0);
    add_exit("fetish", "east",  0);
}
