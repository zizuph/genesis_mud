/*
 * MR3.c
 * Ruins of Kamesh
 * Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A narrow path through stone ruins");
    set_long("   The mist here is thinner than the surrounding "+
	     "ruins. As a result the ground and stone is drier. You "+
	     "are standing on a corner. The ruined buildings tower "+
	     "over you to the north, west and east. Their dark, stone "+
	     "exteriors are broken, cracked, or missing entirely, as are "+
	     "their roofs. The southern side of the road is bordered "+
	     "by a few trees and an expanding field of dark green grass. Off "+
	     "to the southeast you notice a large, dark shape beyond the mist "+
	     "but can't quite make it out from here.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"path", "dirt", "road", "ground", "down"}),
	     "The narrow path through the ruins consists mostly of a "+
	     "thin patch of dirt and pebbles which runs the course of "+
	     "what used to be a large, well-used road. It is now covered "+
	     "in weeds and bushes and is barely recognizeable as a path.\n");

    add_item( ({"buildings", "ruined buildings", "ruins", "stone",
		"stone exteriors", "exteriors", "walls"}),
	     "The ruined buildings tower over you. Even though they are "+
	     "merely a fraction of their original height and width, they "+
	     "are still quite impressive. The dark stone construction "+
	     "is simply designed, but elegant. Most of the buildings are "+
	     "cracked and look as though they could fall over at any "+
	     "moment while others have already begun falling over; entire "+
	     "walls having fallen to the ground.\n");

    add_item( ({"field", "trees", "green grass", "grass", "dark green grass"}),
	     "The field of grass and trees expands out from the ruins "+
	     "to the south and disappears into another cloud of mist "+
	     "several hundred yards out. You aren't quite sure what keeps "+
	     "this area so perpetually moist that it is always smothered "+
	     "under cover of mist and darkness.\n");

    add_item( ({"shape", "large shape", "dark shape", "large dark shape"}),
	     "The large, dark shape off to the southeast is very "+
	     "interesting. It looks like another of the ruined buildings, "+
	     "but there is something different about it. Something "+
	     "distinguishes it from the rest of the buildings but you "+
	     "can't quite tell what it is from here. Perhaps you might "+
	     "figure it out if you got a closer look.\n");

    add_exit(MONKRUIN_DIR + "mr4", "north");
    add_exit(MONKRUIN_DIR + "mr2", "east");
}
