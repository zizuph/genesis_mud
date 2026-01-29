/*	part of Calian tunnel east

	coder(s):	Amelia
	history:	5/2/95		created Amelia
			5/3/95	updated by Amelia
	purpose:	section in Calian tunnel
	exits:		tunnel5(north), tunnel7(south)
	objects:	none
	npcs:		none
	quests:		none
	special:	uses "tunnel_slip"->tunnel is slippery here
			player slips if not dexterous enough
	to do: 
	bugs:		none known
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
	set_long("You continue along the tunnel, which glows in a "+
		"soft crystalline light.  The floor is slippery with "+
		"shallow puddles of liquid.\n");
	add_item("tunnel", "The crystal tunnel continues "+
		"on and glows with a blue light.\n");
	add_item((({"beads", "liquid", "multicoloured liquid"})),
		("The liquid appears to be liquid crystal!\n"));
	add_item("floor", "The floor has small puddles of "+
		"liquid crystal, which makes it somewhat slippery.\n");
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

		
	add_exit(TUNNELS_ROOMS+"tunnel5", "north", "@@slip");
	add_exit(TUNNELS_ROOMS+"tunnel7", "south", "@@slip");
}