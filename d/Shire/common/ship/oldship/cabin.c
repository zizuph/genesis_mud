#pragma save_binary

inherit "/d/Genesis/ship/cabin";
#include "/d/Shire/common/defs.h"


void
create_cabin()
{
    set_short("A small and bad smelling cabin inside the poor ship");
    set_long(break_string("This cabin is rather small and bad smelling. " +
			  "The only furniture is a rough bench in one " +
			  "corner and the ladder leading to the deck above. " +
			  "The only light source in the room is the trapdoor " +
			  "in the ceiling, except for the holes in the " +
			  "ship's hull, of course.\n",75));

    add_item("bench", break_string("This bench is a typical inventory in " +
				   "this ship. Rough and simple.\n",75));

    add_item("ladder", "You wonder if it would support your weight.\n");

     add_exit(SHIP_DIR + "oldship/deck","up",0,1);

}