/*
 * Shield worn by hobgoblins south of Palanthas in a cave.
 *
 * Mortis 10.2006
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../local.h"

public void
create_armour()
{
	set_name("shield");
	set_adj("leathery");
	set_short("leathery shield");
	set_long("Though long, the shield's width is slim.  With a leathery loop "
	+ "and handle studded in place, you aren't quite sure what flesh was "
	+ "tanned to construct the whole armour, but it is thick and sturdy "
	+ "enough to provide extra protection.\n");

	set_at(A_SHIELD);
	set_ac(10 + random(3));
	set_am(({1, 0, -1}));
}
