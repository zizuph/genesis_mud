/*	part of east Calian tunnel

	coder(s):	Amelia
	history:	5/2/95	created by Amelia
			5/3/95	updated by Amelia
	purpose:	part of calian east tunnel
	exits:		north to tunnel9, east to tunnel11

	objects:	none
	npcs:		none
	quests:		none
	special:	somewhat slippery(uses../specials/tunnel_slip.c)
	to do:		
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "tunnels.h"
inherit SLIP;

void
create_room()
{
	set_short("A crystal tunnel");
		
	set_long("A crystal tunnel opens to the north.  To the east "+
		"there is an opening to a cave.  The walls and ceiling "+
		"form a graceful arch overhead and glow softly with a blue "+
		"light.  Beads of multicoloured liquid crystal form on "+
		"the walls and occasionally trickle down.  You notice that "+
		"the floor is quite slippery.\n");

	add_item("tunnel", "The tunnel extends in an east-west direction.\n");
	add_item((({"walls", "ceiling"})),
		"The walls and ceiling are carved from "+
		"blue crystal that is veined with gold and "+
		"silver.  It glows with a mysterious light of its own.\n");
	add_item((({"crystal", "liquid crystal", "beads"})),
		("The walls and ceiling are carved from a solid "+
		"blue crystal that emits light.  Beads of multicolored "+
		"liquid crystal condense on the solid surface, "+
		"and trickle down, making the floor very slippery.\n"));
	add_item("floor", "The floor is very slippery, possibly "+
		"due to small puddles of liquid crystal.\n");

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

		
	add_exit(TUNNELS_ROOMS+"tunnel9", "north", "@@slip");
	add_exit(TUNNELS_ROOMS+"tunnel11", "east", "@@slip");
}