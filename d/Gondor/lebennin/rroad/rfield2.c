/*	This room is rfield2.c and it is the middle field room of 3 between
 *	the arms of the sirith.
 *
 *      (C) Copyright Jim Fraser (Theory)
 *
 */


inherit "/d/Gondor/lebennin/rroad/rfield.c";
 
#include <macros.h>
#include <stdproperties.h>
 
#include "/d/Gondor/defs.h";

void
create_field()
{
    set_extraline("There is a small track through the field here, leading "
	+ "from the road to the east, to the house just to the west. The "
	+ "Pelargir city walls are to the east, visible over the horizon.");

    add_exit(LEB_DIR + "rroad/rr4", "east", 0, 2,);
    add_exit(LEB_DIR + "rroad/rfield1", "north", 0, 2,);
    add_exit(LEB_DIR + "rroad/rfield3", "south", 0, 2,);
    add_exit(LEB_DIR + "rroad/rfield4", "west", 0, 2,);

    add_field();
    add_house();
    add_fence("The path passes through the gate in the fence here, "
	+ "leading up to the house.");
    add_walls();
    add_road();
    add_city();
    add_item(({"path", "track",}),BSN("the path is little more than "
	+ "matted grass from years of being trodden on. It leads to the "
 	+ "house in the west."));

}
