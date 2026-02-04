inherit "/std/room.c";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message) 	break_string(message,70)
create_room()
{
	set_short("Library");
	set_long(BS("The air in this dim room is thick with the musty, unpleasant smell of "
	+ "rotted wood and decaying paper. Torn scrolls, collapsed bookshelves, and "
	+ "mouldy books litter the floor around you. In the center of the room "
	+ "sits a large pile of ashes long turned cold, a mute testimony to the "
	+ "desperation of a frigid winter uncounted years ago. Once-proud tapestries lie "
	+ "in tatters on floor next to the broken remnants of a fine wooden writing desk. "
	+ "Through a cracked wooden arch to the west the library continues.\n"));
 
	add_exit(MANSION + "wing_n3","north",0,1);
	add_exit(LIBRARY + "library_1","west",0,1);
	add_item(({"books","book","scrolls"}),BS("Every book you touch crumbles "
		+ "to dust with the mere brush of your hand. Time's ravages have left their "
		+ "unkind mark on these books; the decades lay heavily on their stained and faded pages.\n"));
	add_item(({"tapestries","tapestry"}),BS("The faded colors on these motheaten silk tapestries "
		+ "must have been brilliant in their day, but now the torn fragments of "
		+ "cloth scattered about the room are nondescript and worthless.\n"));

	add_prop(ROOM_I_INSIDE, 1);		/* indoors room */
	reset_room();
}

reset_room()
{
	object ob;
	
    ob = present("ashes");
	if (ob)
    {
        ob->reset_nash();
    }
    else
    {
        ob = clone_object(LIBRARY + "ashes.c");
        ob->move(this_object());
    }
}
