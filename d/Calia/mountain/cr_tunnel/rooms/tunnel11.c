/*	part of the calian tunnel, entry to tunnel from east

	coder(s):	Amelia
	history:	5/2/95		created by Amelia
			5/3/95	updated by Amelia
	purpose:	part of the calian tunnel
	exits:		west to tunnel10, u to guard_room_E.c
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
	set_short("The crystal tunnel");
	set_long("This is a cave beneath a hollow tree.  The walls and "+
		"ceiling are carved out of blue crystal that emits a "+
		"soft light.  To the east you see what appears to be "+
		"huge tree roots twisting down from above, deeply embedded "+
		"in the walls.  To the west there is an entry to a "+
		"tunnel.  The tree must be very large, for there is a "+
		"crystal stairway that leads right up into it.  The tree is "+
		"coated with a transparent resinous crystal.  You can "+
		"hear sounds from the area above the stairway.\n");

	add_item((({"roots", "tree roots", "tree"})),
		("The room is at the base of a hollow tree, where "+
		"the roots seem to have soaked up the liquid crystal right "+
		"into the tree itself.\n"));
	add_item((({"crystal", "resinous crystal", "liquid crystal"})),
		("There is a strange phenomenon of liquid crystal, that "+
		"has hardened into rock in some spots, and has made the "+
		"tree a part of the crystal wall.\n"));
	add_item((({"wall", "walls"})),
		("The walls are formed out of the crystal that "+
		"is the main feature of this tunnel.  Here, however, "+
		"tree roots have sunk down into the walls, framing a "+
		"room where a stairway goes up right into the tree.\n"));
	add_item((({"stairway", "crystal stairway"})),
		("There is a stairway carved from crystal which "+
		"leads directly up into the tree.\n"));
	add_item((({"tunnel", "crystal tunnel"})),
		("You look west and see that a vast tunnel stretches "+
		"far ahead.  The tunnel appears to be carved from "+
		"crystal, and glows with a soft light.\n"));

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

		
	add_exit(TUNNELS_ROOMS+"tunnel10", "west", 0,0);
	add_exit(TUNNELS_ROOMS+"guard_room_E", "up", 0,0);
}