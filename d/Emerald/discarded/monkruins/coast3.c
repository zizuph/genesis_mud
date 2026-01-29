/*
 * COAST3.c
 * This is the coastal road/path leading to the monk ruins.
 * The monk ruins appear in a hazy, ocean mist from here.
 * - Alaron November 1996
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Mist-shrouded cliffside path");
    set_long("   The well-travelled path is covered in a fine sheet of "+
	     "mist here, blanketing the flattened weeds and bushes in "+
	     "a sheen of sparkling dew. The path continues further to "+
	     "the south where the low sheet of mist begins to thicken "+
	     "into a dark fog. Deep within the fog you notice several "+
	     "dark, looming shadows. The shadows appear to be buildings "+
	     "or structures of some kind. The thick line of trees "+
	     "borders the path on the west and the cliffs to the east "+
	     "and north.\n\n");

    add_item( ({"path", "well-travelled path"}),
	     "The path is covered in a fine sheet of mist here. It "+
	     "blankets the grass and weeds, forming a glistening "+
	     "sheet of dew.\n");

    add_item( ({"weeds", "bushes", "flattened weeds",
		"flattened bushes", "grass", "ground", "dirt",
		"down"}),
	     "The flattened weeds and bushes of the well-travelled "+
	     "path are covered with a thin, glistening coat of "+
	     "dew. A thin mist hangs over the path.\n");

    add_item(({"dew", "sparkling dew", "glistening dew"}),
	     "The dew on the weeds, grass and the ground "+
	     "glistens in the sunlight which permeates the thin "+
	     "sheet of mist hanging over the ground.\n");

    add_item( ({"mist", "sheet of mist", "blanket", "low sheet of mist", 
		"low sheet"}),
	     "The low sheet of mist hangs ominously over the ground, "+
	     "concealing everything below your ankles in a dark gray "+
	     "haze and covering the ground with a glistening dew.\n");


    add_item( ({"shadows", "dark shadows", "looming shadows",
		"dark looming shadows", "distance", "structures",
		"buildings", "ruins"}),
	     "Off in the distance, you peer through the gathering "+
	     "fog to the south and east. Looming behind the veil "+
	     "of grayness, you can see dark shadows concealed "+
	     "therein. They are tall and resemble the outlines of "+
	     "buildings or structures of some kind, but you can't "+
	     "tell for sure from this distance.\n");


    add_item( ({"cliffs", "cliff", "ocean cliffs"}),
	     "The bushes and grass extend out from the path "+
	     "toward the east and north, where they abruptly "+
	     "are cut short by the ocean cliffs, dropping "+
	     "incredible distances down to the ocean shore below.\n");


    add_item( ({"trees", "line of trees", "thick line of trees"}),
	     "The thick line of trees borders the path on the "+
	     "west, mirroring the direction of the path at "+
	     "every turn.\n");

    add_exit(MONKRUIN_DIR + "coast4", "south");
    add_exit(MONKRUIN_DIR + "coast2", "northwest");

}

    
