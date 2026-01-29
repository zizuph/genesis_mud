/*
 * 2k6.c
 * Second Floor Hallway, Castle Telberin, Intersection.
 *  - Alaron September 11, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Hallway");
    set_long("   You stand in front of an enormous, intricately carved "+
	     "archway which leads out of the hall into a dimly lit "+
	     "room to the west. To the north, through the amber glow of "+
	     "the wall lamps, you can hear the noise of the crowd getting "+
	     "louder as the hallway decorations become more extavagant "+
	     "and more luxurious. The hallway here branches off in two "+
	     "directions, to the north and northeast.\n\n");

    add_item(({"arch", "intricately carved arch", "archway", "room",
	       "west"}),
	     "The tall, vaulted arch is extremely well decorated in carvings "+
	     "of beautiful nudes surrounded by relief carvings of trees and "+
	     "vines of twirling ivy. At the top of the arch is the depiction "+
	     "of a small cherub. Peering underneath the arch at the room "+
	     "to the west, through the dim lighting, you notice several "+
	     "tables and a long couch.\n");

    add_item(({"tables", "couch", "long couch"}),
	     "You can't quite make out the details of the furniture from "+
	     "here.\n");

    add_item(({"lamp", "lamps", "wall lamps"}),
	     "The wall lamps appear to be very valuable. Their bases look "+
	     "like hand-shaped gold and silver with intricately blown "+
	     "glass tops.\n");

    add_item(({"decoration", "decorations"}),
	     "The decorations in the hallway leading to the north are "+
	     "of mythical scenes, local scenes from the city and other "+
	     "invented pictures of life outside the Kingdom.\n");

    
   add_exit(CASTLE_DIR + "2k7","west",0);
   add_exit(CASTLE_DIR + "2k13","northeast",0);
   add_exit(CASTLE_DIR + "2k8","north",0);
}
