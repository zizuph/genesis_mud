/*
 * Cave room tells, hobgoblins.  Add this to rooms
 * in which you want cave noises to be heard.
 *
inherit CAVE + "cave_noises";

void
create_room()
{
	set_tell_time(x);
	add_tell("@@get_tells@@" + "\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
 *
 * Mortis 11.2006
 *
 */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

string
get_tells()
{
	string cavetell;

	cavetell = one_of_list(({"A drop of water falling into a puddle "
	+ "somewhere nearby echoes off the cave walls.",
	  "A drop of water falls onto the cave floor from a stalactite "
	+ "overhead.",
	  "\"Drip.\"",
	  "The skittering of tiny, chitinous legs echoes about the walls from "
	+ "somewhere closeby.",
	  "A breeze picks up for a moment bringing with it the smell of "
	+ one_of_list(({"warm piss", "crap", "rot and sludge", "rotting meat",
	  "sour trash", "mold"})) + ".",
	  "The splash of something running through a puddle echoes about from "
	+ "closeby.",
	  "A grunt or a snarl echoes faintly about the walls from closeby."}));

	return cavetell;
}
