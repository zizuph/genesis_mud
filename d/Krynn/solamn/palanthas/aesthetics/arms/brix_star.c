/*
 * Throwing stars used by Brix ganger off Jems Court
 * in the Aesthetics quarter of Palanthas.
 *
 * The hit is higher than normal, because it cannot be
 * wielded and it is two handed.  It can only be used by
 * npc Brix gangers or guilds that can throw knives.
 * Another downside is that they wear out very quickly.
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
	set_name("star");
	set_adj(({"throwing", "three-bladed", "bladed"}));
	set_short("three-bladed throwing star");
	set_long("Three polished steel blades curving to a point at their ends "
	+ "come together around a flat ring of steel to form this palm-sized, "
	+ "star weapon designed for highly accurate spinning throws.\n");

	set_hit(25);
	set_pen(20);
	set_wt(W_KNIFE);
	set_dt(W_SLASH | W_IMPALE);
	set_hands(W_BOTH);
	set_likely_dull(14);
	set_keep(1);
	set_wf(TO);
}

public mixed
wield()
{
	return "There is no handle or place to wield this weapon.  A skilled "
	+ "knife thrower, however, would have no problem flinging it in battle.\n";
}
