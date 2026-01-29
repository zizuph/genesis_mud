// file name: d/Avenir/common/outpost/fort4.c
// creator(s):  Kazz    Feb '95
// last update:
// purpose:     outpost dining area
// note:	where outpost dwarves eat
// bug(s):
// to-do:       add items
//		have a real food shop here? Or just free food for guards?

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/std/room";

create_room()
{
        SHORT("Outpost eating area");
        LONG( "This noisy, rumbling room is full of long tables and "+
	      "benches. Dwarves are eating and drinking here, talking "+
	      "loudly and guffawing. The room itself has a doorway exiting "+
	      "south. The wall and ceiling appear to be natural, part of "+
	      "the cavern itself.\n" );

        add_exit(OUTPOST + "fort1","west",0);
        add_exit(OUTPOST + "fort5","south",0);

	add_item(({"table", "tables", "bench", "benches"}),
                 "The tables and benches are wooden and sturdy.\n" );
	add_item(({"dwarves"}),
                 "The dwarves are eating and relaxing.\n" );
	add_item(({"doorway"}),
                 "It leads south to the middle of the fort.\n" );
	add_item(({"wall", "ceiling"}),
                 "The north wall and ceiling are naturally smooth, and "+
		 "curves overhead to the south.\n" );
	add_item(({"cavern"}),
                 "The cavern has been used to provide some walls and "+
		 "ceiling for the fort.\n" );

        LIGHT
        IN

} // create_room()
