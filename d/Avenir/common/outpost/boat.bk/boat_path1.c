// file name: d/Avenir/common/outpost/boat_path1.c
// creator(s):  Kazz    Feb '95
// last update:
// purpose:     leads from outpost to beach with boat
// note:	
// bug(s):
// to-do:       

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

#pragma save_binary

inherit "/std/room";

create_room()
{
        SHORT("Short tunnel");
        LONG( "You are in a very short tunnel in the cavern rock. The tunnel "+
	      "opens up almost immediately to the northeast, leading to a "+
	      "sandy beach and the edge of water. The white glowing "+
	      "light is stronger in that direction. You can enter the fort "+
	      "to the southwest.\n" );

        add_exit(OUTPOST + "boat/boat_path2","northeast",0);
        add_exit(OUTPOST + "fort7","southwest",0);

	add_item(({"tunnel", "cavern", "cavern rock"}),
                 "The cavern rock is rather non-descript.\n" );
	add_item(({"light", "white light", "glowing light"}),
                 "The light is much brighter to the northeast.\n" );
        add_item(({"beach", "sandy beach"}),
                 "The beach is on the edge of the calm water.\n" );
        add_item(({"water"}),
                 "The water seems to be part of a large body of water.\n" );

        LIGHT
        IN_IN

} /* create_room() */
