/*
 * Sewer room tells, Aesthetics.  Add this to rooms
 * in which you want sewer noises to be heard.
 *
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
 * Mortis 05.2006
 *
 */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

string
get_tells()
{
	string sewtell;

	sewtell = one_of_list(({"A drop of water falling into a puddle somewhere "
	+ "nearby echoes about the walls.",
	  "\"Drip.\"",
	  "The skittering of tiny claws echoes about the walls from somewhere "
	+ "closeby.",
	  "\"Squeak, Qweak.\"",
	  "The low clang of a large, metal pipe resounds throughout the area.",
	  "You hear the clung of a large, metal pipe echoing about the walls "
	+ "from somewhere " + one_of_list(({"nearby.", "above.", "below."})),
	  "A piece of brick or small stone clatters briefly nearby.",
	  "The floor groans and gurgles below you momentarily.",
	  "Water splashes through a crack overhead and splooshes down the "
	+ "wall.",
	  "\"Tink... tink... tink...\"",
	  "The scurrying of hundreds of tiny clawed feet nearby echoes about the "
	+ "walls.",
	  "The breeze gusts for a moment bringing with it the smell of "
	+ one_of_list(({"warm piss", "crap", "raw sewage", "rotting meat", "sour "
	+ "apples", "spoiled milk"})) + ".",
	  "A damp breeze blows briefly against your face.",
	  "\"Grorble... smoksh...\"",
	  "The high-pitched hissing of steam bursting free pierces the air and "
	+ "then is gone, echoing about the walls an instant longer.",
	  "The cool, damp breeze brings with it a low whisper.",
	  "The splash of something running through a puddle echoes about from "
	+ "closeby."}));

	return sewtell;
}
