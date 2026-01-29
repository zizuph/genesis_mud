/*	part of eastern Calian tunnel

	coder(s):	Amelia
	history:	5/2/95		created Amelia
			5/3/95	updated by Amelia
          updated 23/MAY/95 Digit - added add_items
	purpose:	part of Calian tunnel
	exits:		tunnel2(north), tunnel4(south)
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
	set_long("You walk along the corridor of the tunnel.  "+
		"It is very quiet here, except for the sound of your "+
		"footsteps.  The walls and ceiling of the tunnel "+
		"sparkle in the dim blue light, and you can make out "+
		"fine veins of gold and silver that are embedded in the "+
		"crystal.  You notice that the air is becoming warm "+
		"and humid.\n");

	add_item("crystal", "The blue crystal emits a soft light "+
		"and is laced with fine veins of glittering, precious "+
		"metals.\n");
	add_item("tunnel", "The tunnel is carved from solid "+
		"crystal.\n");
	add_item((({"walls", "ceiling"})),
		("The walls and ceiling of the tunnel meet in an "+
		"arch overhead.\n"));
    add_item((({"veins","gold","silver"})),"You see fine veins of "+
        "gold and silver that are firmly embedded in the crystal.\n");

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

		
	add_exit(TUNNELS_ROOMS+"tunnel2", "north", 0,0);
	add_exit(TUNNELS_ROOMS+"tunnel4", "south", 0,0);
}