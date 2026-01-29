/*
 * MR4.c
 * Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Center of a ruined monastery");
    set_long("   You are standing in what probably was the center "+
	     "of the monastery that used to thrive here. The toppled "+
	     "buildings are all around you, their leaning, cracked "+
	     "surfaces seem to be waiting for some final exhale which "+
	     "would allow them to come crashing down into this center "+
	     "square. The narrow, weed-covered paths extends to the "+
	     "northwest, north, east, and south from here. Various "+
	     "tall buildings lie scattered between the path, cracked "+
	     "and decaying. A chill wind blows across the square, "+
	     "wailing as it passes between and through the crumbled "+
	     "monastery.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"path", "road", "ground", "down", "narrow path",
		"weed-covered path"}),
	     "The narrow path is not much more than a few patches of "+
	     "dirt and pebbles amidst a warren of tangled weeds and "+
	     "low grass.\n");

    add_item( ({"buildings", "ruins", "square", "toppled buildings",
		"ruined buildings", "monastery", "ruined monastery"}),
	     "The buildings are in terrible shape. It looks like it "+
	     "has been centuries since any of these structures stood "+
	     "tall and proud. Despite the simplistic, sturdy design "+
	     "of the buildings, something must have been strong enough "+
	     "to tear this place down. You wonder whether it was an "+
	     "earthquake or something less mundane.\n");

    add_exit(MONKRUIN_DIR + "mr5", "northwest");
    add_exit(MONKRUIN_DIR + "coast8", "north");
    add_exit(MONKRUIN_DIR + "mr1", "east");
    add_exit(MONKRUIN_DIR + "mr3", "south");
}
