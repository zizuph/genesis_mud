/*	part of Calian tunnel 
	
	coder(s):	Amelia

	history:	5/2/95		created Amelia
			5/3/95 updated descriptions by Amelia
	purpose:	part of Calian tunnel
	
	exits:		connects to tunnel1(north) and tunnel3(south)

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
	set_long("The tunnel goes north and south here.  The crystal lights "+
		"the area with a soft glow.  Small veins of gold "+
		"and silver thread the crystal walls and ceiling and make "+
		"it sparkle.\n");


	add_item((({"tunnel", "crystal", "light", "glow"})),
		("The tunnel is carved out from blue "+
		"crystal which emits a soft light.\n"));
	add_item((({"veins", "gold", "silver"})),
		("Precious metals are embedded in the crystal.\n"));

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

	add_exit(TUNNELS_ROOMS+"tunnel1", "north", 0,0);
	add_exit(TUNNELS_ROOMS+"tunnel3", "south", 0,0);
}