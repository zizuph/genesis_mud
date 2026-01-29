// Ziggurat galleria (room1.c)
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
    set_short("northwest galleria, between a shop and the bank");
    set_long("You are walking along the galleria of the Ziggurat. "+
	"Glossy black stone surrounds you with openings to the north "+
	"and the west. To the southeast you can see a black rail that "+
	"surrounds the overlook to the plaza below and the "+
	"@@see_tree@@.@@see_nearby@@\n");

    add_exit("room2", "east",  0);
    add_exit("room8", "south", 0);

    add_exit("bank",      "north", 0);
    add_exit("makeovers", "west",  0);

    add_item(({"bank"}),
	"North is the bank.\n");
    add_item(({"shop"}),
	"West is a shop.\n");
}
