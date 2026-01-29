/*	part of eastern calian tunnel 

	coder(s):	Amelia
	history:	5/2/95		created by Amelia
			5/3/95	updated by Amelia
	purpose:	part of calian tunnel
	exits:		north to tunnel8, south to tunnel10
	objects:	none
	npcs:		none
	quests:		none
	special:	very slippery here (uses../specials/very_slip.c)
	to do:		
	bugs:		none known
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
	set_long("The tunnel narrows and the ceiling becomes lower.  "+
		"You notice that the air is quite warm and humid here.  "+
		"The floor is as slippery as ice.  There is a soft "+
		"blue light that guides your path; however, you can't "+
		"see very far ahead.\n");

	add_item((({"tunnel", "walls"})),
		("The tunnel is narrow here, as though the walls are "+
		"closing in.\n"));
	add_item("floor", "The floor is very slippery, "+
		"perhaps due to the liquid crystal, that is beginning "+
		"to form puddles at your feet.\n");
	add_item((({"light", "blue light"})),
		("The soft light emanates from the crystal.\n"));


	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);

		
	add_exit(TUNNELS_ROOMS+"tunnel8", "north", "@@slip");
	add_exit(TUNNELS_ROOMS+"tunnel10", "south", "@@slip");
}