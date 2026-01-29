/*	tunnel8, part of east calian tunnel--contains pool
	of "liquid crystal", and very slippery here;)

	coder(s):	Amelia
	history:	10/2/95		created by Amelia
	purpose:	wolf den, part of tunnel system
	exits:		through pool, to tunnel8
	objects:
	npcs:
	quests:		not yet
	special:	
	to do:
	bugs:		none known
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "tunnels.h"
inherit ROOM_TELL;

void
create_room()
{
	set_short("A large cave");
	set_long("You find yourself in a large cave with a low ceiling.  "+
		"The walls and floor are carved from the same "+
		"luminescent crystal as the rest of the tunnel.  There "+
		"is a hole in the ceiling that opens to "+
		"night sky and a full moon shining above. Around on "+
		"the floor are scattered bones that are encased in "+
		"crystal.\n");

	add_item((({"cave", "dome"})),
		("This is a cave with a low ceiling, which looks "+
		"like the den of a wolf pack.\n"));
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
		
}

void
enter_inv(object ob, object from)
{
	::enter_inv(ob, from);
	if (interactive(ob))
	{
	write("The moon shines down on the crystal pool.\n");
	}
}
