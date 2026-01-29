// file name: d/Avenir/common/outpost/cave3.c
// creator(s):  Kazz    Jan '95
// last update:
// purpose:     outpost side of the chasm.
// note:
// bug(s):
// to-do:	allow a 'jump' which plummets the player to the bottom of
//		    the chasm.  If they don't die, they will be stuck.
//		future: allow a rope to be tied to a rock to climb down?
//

#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"

inherit "/d/Avenir/inherit/room";

void
create_domain_room()
{
    set_short("north side of the abyss");
    set_long("You stand on the north side of a huge chasm. "+
        "The bright flames to the northeast illuminate the "+
        "edge on the opposite side of the chasm. "+
        "The black fortress blends into the surrounding stone "+
	    "of the massive magma tube that leads upwards to the "+
        "northeast. "+
		"To the northwest there is a jagged opening in "+
        "the wall. Light seems to flicker and flash from in"+
        "side. A stone bridge crosses the lava-filled chasm.\n");
	
	add_exit("cave2",     "northeast",0);
    add_exit("tomb",      "northwest", 0);
	add_exit("bridge",    "south", 0);
	add_exit("secret/stair_top", "down", 0, 30, 1);

	FORT
	TOWER
	GATE
	FLAME
	CAVERN
	WALL
	PATH
	FLOOR
	ROCKS
      LIGHT
      IN

	
    add_item(({"chasm", "abyss"}),
	  "The chasm is at least fifty feet wide, and the bottom "+
	  "is smothered in glowing lava.\n");
    add_item(({"bridge"}),
        "This bridge is made entirely of stone. It has been "+
        "built into the wall of the chasm itself. Its footings are "+
        "quite huge to support the weight of the bridge.\n");
    add_item(({"footings", "down"}),
	    "As you look down to examine the footings you see that there "+
        "is a small ledge just a short distance below, probably used "+
        "support the footings of the bridge.\n");
    add_item(({"ledge"}),
	    "The ledge is just a short distance down. It appears to be "+
        "where the footings of the bridge rest.\n");
    add_item(({"edge"}),
	    "The opposite side of the chasm is barely lit by the "+
	    "flames. It is rather far away.\n");
    add_item(({"opening", "jagged opening", "northwest"}),
        "Lights seem to come from inside a hole in the "+
        "in the wall.\n");

    add_cmd_item(({"chasm", "across", "across chasm"}),
	  ({"jump", "cross"}),
	  ("If you tried to jump, you might fall to your "+
	   "death.\n"));
 
} // create_room()


