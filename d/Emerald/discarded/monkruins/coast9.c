/*
 * COAST9.c
 * Coastal Road leading into the ruins of Kamesh.
 * Inside the gate.
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("Dark, foggy path");
    set_long("   You are standing on a narrow, overgrown path. The barely "+
	     "visible dirt on the ground is covered with pebbles and small "+
	     "growing bushes and plants. A thick, heavy fog hangs over "+
	     "the area, draping it with blanketing moisture. The path "+
	     "continues into the fog to the west and curves northeast where "+
	     "the mist seems to lift some. To the northeast, you can see " +
             "the entrance to a monastery.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"path", "ground", "down", "gravel", "pebbles", "dirt",
		"road", "weeds", "plants", "bushes"}),
	     "The dirt road beneath you seems small and narrow. It is "+
	     "covered with weeds and wild growing plants, hiding the "+
	     "original size of the ancient pathway.\n");
    
    add_item( ({"fog", "thick fog", "heavy fog", "thick heavy fog",
		"mist", "moisture", "blanket"}),
	     "The thick, heavy fog looms over the area. It casts a "+
	     "dull gray filter over all of the colors, deadening the "+
	     "once brilliant colors of the surrounding wood and "+
	     "plants.  The monastery walls seem dark and black underneath "+
	     "the veil of mist.\n");

    add_item("monastery",
        "The walls of the monastery obstruct any view within from here.\n");

    add_item(({ "walls", "outer walls" }),
        "The three-storey walls surround the monastery, obstructing " +
        "any view inside.\n");

    add_exit("coast8", "west");
    add_exit(MONASTERY_DIR + "m0_00", "northeast");
}
