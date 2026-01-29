/*	entrance to the tunnels that connect with Calian palace

	coder(s):	Amelia

	history:	5/2/95	created Amelia
			5/3/95	 descriptions, etc. updated by Amelia

	purpose:	part of Calian tunnel

	exits:		connects with hallway(up) and tunnel2(south)
	objects:	none
	npcs:		none
	quests:		none
	special:	none
	to do:	
	bugs:		none known
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "tunnels.h"

void
create_room()
{
	set_short("A crystal tunnel");
	set_long("This cavern is an entrance to a vast tunnel.  "+
		"The high ceiling and walls are carved from "+
		"blue crystal.  It glows with a soft light "+
		"so that you can see your surroundings very well, "+
		"but you can't see that far ahead.  It is very still "+
		"here as though insulated from the outside.  "+
		"There is a stairway in the north wall "+
		"that leads up.  The tunnel opens to the south.\n");
	
	add_item((({"rock", "walls", "ceiling"})),
		("The walls and ceiling are carved from blue crystal that "+
		"glows with a mysterious blue light.\n"));
	add_item((({"staircase", "stairs"})),
		("The stairway appears to be carved directly "+
		"from the crystal, and leads up.\n"));

	add_item((({"crystal", "rock", "blue crystal"})),
		("The blue crystal is very beautiful, and "+
		"glows with its own light.\n"));
	add_item((({"tunnel"})),
		("The tunnel appears to have been carved right out "+
		"crystal.  You wonder who could have carved "+
		"it, or how it got here.\n"));
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);
		
	add_exit(TUNNELS_ROOMS+"hallway", "up", 0,0);
	add_exit(TUNNELS_ROOMS+"tunnel2", "south", 0,0);
}