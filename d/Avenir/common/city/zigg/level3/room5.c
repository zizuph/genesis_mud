// Ziggurat galleria (room5.c)
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
    set_short("southeast galleria, between two shops");
    set_long("You are walking in the galleria of the Ziggurat. "+
	"Glossy black stone surrounds you with openings to the east "+
	"and the south. To the northwest you can see a black rail that "+
	"surrounds the overlook to the plaza below and the "+
	"@@see_tree@@.@@see_nearby@@\n");

    add_exit("room4", "north", 0);
    add_exit("room6", "west",  0);

    add_exit("candy",     "east",  0);
    add_exit("perfumery", "south", 0);

    add_item(({"shop","shops"}), "Which shop?\n");
    add_item(({"east shop"}),
	"To the east is a shop.\n");
    add_item(({"south shop"}),
	"To the south stands Scentiments, a shop that sells perfumes "+
	"and colognes.\n");

    add_tell("A multitude of scents emanates from the shop to the south.\n");
}

public void
hook_smelled(string str)
{
    if (strlen(str))
	return;

    write("You can make out a stream of various scents coming "+
	"from the south.\n");
}
