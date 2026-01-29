/*	tunnel8, part of east calian tunnel--contains pool
	of "liquid crystal", and very slippery here;)

	coder(s):	Amelia
	history:	5/2/95		created by Amelia
			5/3/95	updated by Amelia
	purpose:	part of east calian tunnel
	exits:		north to tunnel7, south to tunnel9
	objects:	none
	npcs:		none
	quests:		not yet
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
	set_long("The tunnel suddenly opens into a huge cave "+
		"with a vast high dome.  Just to your west there is "+
		"a large pool of what appears to be liquid crystal.  "+
		"There is a very narrow path that runs along the "+
		"pool on the east side to an arched exit beyond, "+
		"where apparently the tunnel continues.\n");

	add_item((({"path", "narrow path"})),
		("The path is very narrow and looks quite slippery!\n"));
	add_item((({"tunnel", "exit"})),
		("Far across the cave, you see an exit where the "+
		"tunnel continues.\n"));
	add_item((({"cave", "dome"})),
		("This is a large domed cave, the ceiling and floors "+
		"of which are covered in multicolored crystal.\n"));
	add_item((({"crystal", "liquid crystal"})),
		("The crystal is both solid and liquid here.  "+
		"The ceiling and walls are studded with crystal gems, "+
		"rubies, sapphires, emeralds, amethysts, and diamonds.  The "+
		"liquid pool reflects these colors in a soft glow.\n"));
	add_item("pool", "The pool of liquid crystal glows "+
		"softly with a mysterious light.  It would not "+
		"be a good idea to go wading in though, unless "+
		"you want to become part of the crystallized scenery.\n");
	add_item((({"light", "soft light"})),
		("The source of the light appears to be from "+
		"the crystal, yet it remains a mystery.\n"));



	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);
		
	add_exit(TUNNELS_ROOMS+"tunnel7", "north", "@@slip");
	add_exit(TUNNELS_ROOMS+"tunnel9", "south", "@@slip");
}
