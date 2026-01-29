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

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"

inherit "/std/room";

create_room()
{
	SHORT("North side of chasm");
	LONG( "You stand on the north side of a huge chasm. The bright "+
	      "flames to the northeast illuminate the edge on the opposite "+
	      "side of the chasm. The black fort squats darkly against "+
	      "the cavern wall as if trying to hide from the intensity of "+
	      "the flames. To the northwest there is a jagged opening in "+
              "the cavern wall. Light seems to flicker and flash from in"+
              "side. A stone bridge crosses the dark chasm.\n" );
	
	add_exit(OUTPOST + "cave2","northeast",0);
        add_exit(OUTPOST + "tomb", "northwest", 0);
	add_exit(OUTPOST + "bridge","south",0);
	FORT
	TOWER
	GATE
	FLAME
	CAVERN
	WALL
	PATH
	FLOOR
	ROCKS
	
 //     CHASM
        add_item(({"chasm"}),
		 "The chasm is at least fifty feet wide, and the bottom "+
		 "is smothered in darkness.\n");
	add_item(({"bridge"}),
		 "The bridge isn't the sturdiest, but it is made of stone.\n");
	add_item(({"edge"}),
		 "The opposite side of the chasm is barely lit by the "+
		 "flames. It is rather far away.\n");
        add_item(({"opening", "jagged opening"}),
                 "Lights seem to come from inside. It is in the "+
                 "cavern wall to the northwest\n");

	add_cmd_item(({"chasm", "across", "across chasm"}),
		     ({"jump", "cross"}),
		     ("If you tried to jump, you might fall to your "+
		      "death.\n"));
 
	LIGHT
	IN

} // create_room()


