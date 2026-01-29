inherit "/std/food";

#include "/d/Krynn/common/defs.h"
#include <macros.h>

create_food()
{
	set_amount(100);
	set_name("honey");
	 add_name("plate");
	set_pname("plates");
	 add_pname("honeys");
	set_short("little plate with honey");
	set_pshort("little plates with honey");
	set_long(BS(
		"A drop of fresh yellow honey rests in the middle of "
		+ "the neat plate. It smells fantastic. You can't "
		+ "resist to lick it up.", 70));
}
init()
{
	ADD("eat_it","lick");
}

void
consume_text(object *arr, string vb)
{
	write(BS(
		"You slowly start to lick the liquid honey from "
		+ "the plate. It tastes as delicious as it smelled "
		+ "so you continue eagerly till it is all gone. "
		+ "You feel like a sweet guy now!", 70));
	say(QCTNAME(TP) + BS(
		" licks up hastily all the honey on the plate "
		+ "and, after having finished, "
		+ "looks up smiling with honey all around "
		+ POSSESSIVE(TP) + " mouth.", 70));
}