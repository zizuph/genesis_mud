/*
 * Improvised knife used by Brix gangers behind Jems court
 * in the Aesthetics quarter of Palanthas.
 *
 * Mortis 05.2006
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("shank");
	add_name("knife");
	set_adj(({"dirty", "hemp-handled"}));
	set_short("dirty hemp-handled shank");
	set_long("With a handle that is little more than a wrap of dirty hemp "
	+ "this improvised knife looks more likely to cause an infection than "
	+ "a lethal wound.\n");

	set_hit(9);
	set_pen(9);
	set_wt(W_KNIFE);
	set_dt(W_IMPALE);
	set_hands(W_ANYH);
}
