// Ziggurat galleria (room7.c)
// creator(s):   Zielia + Lucius 2006
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
    set_short("southwest galleria, between two shops");
    set_long("You are walking in the galleria of the Ziggurat. "+
    "Glossy black stone surrounds you with openings to the north "+
    "and the east. To the northeast you can see a black rail that "+
    "surrounds the overlook to the plaza below and the "+
    "@@see_tree@@.@@see_nearby@@\n");

    add_exit("room8", "north", 0);
    add_exit("room6", "east",  0);

    add_exit("makeup",   "west",  0);
    add_exit("clips", "south", 0);

    add_item(({"shop","shops"}), "Which shop?\n");
    add_item(({"west shop"}),
    "Over to the west is Cosmetics by Lyrelle, a shop "+
    "catering to your beauty needs.\n");
    add_item(({"south shop"}),
    "To the south is Tangles, a shop selling adornments for the hair.\n");
}
