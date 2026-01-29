// file name: d/Avenir/common/outpost/fort7.c
// creator(s):  Kazz    Feb '95
// last update:
// purpose:     Natural cave archway, leading ne to boat to Bazaar Island
// note:	
// bug(s):
// to-do:       

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/std/room";

create_room()
{
        SHORT("Natural archway");
        LONG( "The cavern walls and ceiling end just to the northeast in a "+
	      "natural archway. Beyond lies a tunnel dimly lit by glowing "+
	      "white light. Southwest "+
	      "leads into the center of the fort where you can also see a "+
	      "tower at the far corner of the fort. A building is being "+
	      "constructed to the south.\n" );

        add_exit(OUTPOST + "boat/boat_path1","northeast",0);
        add_exit(OUTPOST + "fort5","southwest",0);
// what to put in fort 8?
//      add_exit(OUTPOST + "fort8","south",0);

	add_item(({"tower", "black tower"}), 
                 "The black tower rises high above you to the southeast.\n");
	add_item(({"archway", "natural archway"}),
                 "The natural archway provides entrance and exit to the "+
		 "fort.\n" );
	add_item(({"cavern", "ceiling"}),
                 "The cavern walls bend up to form the ceiling, stretching "+
		 "to the southwest.\n" );
	add_item(({"light", "white light", "glowing light"}),
                 "You can barely notice it from here.\n" );
        add_item(({"building"}),
                 "The building, really just walls, is just being built. "+
                 "You can't yet determine what it will be.\n" );

        LIGHT
        IN

} // create_room()
