/*	part of eastern Calian tunnel

	coder(s):	Amelia
	history:	5/2/95		created Amelia
			5/3/95	updated by Amelia
	purpose:	part of Calian tunnel
	exits:		tunnel3(north), tunnel5(south)

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
		"It is very quiet here.  Overhead the walls and ceiling "+
		"meet in a graceful arch.  The crystal glow continues to "+
		"light your path.\n");
		

	add_item("crystal", "The blue crystal emits a soft light "+
		"and is laced with fine veins of glittering, precious "+
		"metals.\n");
	add_item("tunnel", "The tunnel is carved from solid "+
		"crystal.\n");
	add_item((({"walls", "ceiling"})),
		("The walls and ceiling of the tunnel meet in an "+
		"arch overhead.\n"));

	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

		
	add_exit(TUNNELS_ROOMS+"tunnel3", "north",0,0);
	add_exit(TUNNELS_ROOMS+"tunnel5", "south", 0,0);
}