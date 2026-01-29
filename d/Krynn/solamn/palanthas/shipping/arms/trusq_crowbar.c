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
	set_name("crowbar");
	add_name("bar");
	set_adj(({"iron", "crow"}));
	set_short("small iron crowbar");
	set_long("This darkened iron bar of metal flattens at its ends where it "
	+ "curves in opposite directions providing leverage for popping boxes "
	+ "or other things apart.\n");

	set_hit(13);
	set_pen(10);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);
}

