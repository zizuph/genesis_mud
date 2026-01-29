/*
 * Mortis 03.2006
 *
 * Improvised weapons used by merchant house Trusq
 * warehouse workers in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("gaff");
	add_name("hook");
	set_adj(({"dull", "iron"}));
	set_short("dull iron gaff");
	set_long("Little more than a hook with a handle, this gaff is more often "
	+ "used to catch bags, sacks, or even fish than used as a weapon.\n");

	set_hit(12);
	set_pen(14);
	set_wt(W_CLUB);
	set_dt(W_IMPALE);
	set_hands(W_ANYH);
}

