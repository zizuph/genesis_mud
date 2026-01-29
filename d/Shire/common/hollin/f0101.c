#include "forest.h"

create_forest()
{
    set_short("In a little clearing");
    set_long(
	"Though the forest is dark, here you have arrived in a clearing, "+
	"making the sky a little more visible. You can hear the song "+
	"of a river trickling in the east.\n");

    add_item("clearing",
	"This is a clearing in a forest, making you able to study the sky.\n");
    add_item(({"song", "river", "sound"}),
	"Alas! There must be a river further east from here!\n");

    NORTH("f0102");
    NORTHEAST("f0202");
    EAST("f0201");
    SOUTHEAST("f0200");
    SOUTH("f0100");
    SOUTHWEST("f0000");
    WEST("f0001");
    NORTHWEST("f0002");
}
