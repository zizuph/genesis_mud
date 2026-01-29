// Ziggurat galleria (room2.c)
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
    set_short("northern galleria, south of the stair");
    set_long("You are walking in the galleria of the Ziggurat. "+
	"Glossy black stone surrounds you with main stairwell to the "+
	"north. To the south you can see a black rail that "+
	"surrounds the overlook to the plaza below and the "+
	"@@see_tree@@.@@see_nearby@@\n");

    add_exit("room1", "west",  0);
    add_exit("room3", "east",  0);
    add_exit("stairs", "north", 0);

    add_item(({"stairs","stairwell"}),
	"To the north is the stairwell that provides entry and egress "+
	"from the galleria.\n");
}
