/*	part of Calian tunnel= tunnel7...getting slippery here.

	coder(s):	Amelia
	history:	5/2/95		created by Amelia
			5/3/95	updated by Amelia
	purpose:	part of Calian tunnel
	exits:		tunnel6(north), tunnel8(south)
	objects:	none
	npcs:		none
	quests:		none
	special:	uses very_slip.c from ../specials
	to do:
	bugs:  		none known
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "tunnels.h"
inherit VERY_SLIP;

void
create_room()
{
	set_short("A crystal tunnel");
	set_long("Your footsteps echo in the hollow tunnel "+
		"as you walk along, guided by the soft "+
		"light from the crystal.  Drops of liquid crystal "+
		"form on the walls, and occasionally trickle down.  It "+
		"is very slippery here.\n");

	add_item("tunnel", "The tunnel is carved from "+
		"blue crystal.  It is quite empty here, but somehow "+
		"very slippery.\n");
	add_item("floor", "The floor of the tunnel is becoming "+
		"very slippery, due to small puddles of liquid "+
		"crystal forming there.\n");
	add_item("light", "The crystal emits a soft light.\n");
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

		
	add_exit(TUNNELS_ROOMS+"tunnel6", "north", "@@slip");
	add_exit(TUNNELS_ROOMS+"tunnel8", "south", "@@slip");
}
