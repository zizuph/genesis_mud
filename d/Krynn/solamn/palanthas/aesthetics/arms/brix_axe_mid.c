/* 
 * Mid level axe of Brix gang in aesthetics quarter of Palanthas.
 *
 * Mortis 06.2006
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("head");
	add_name(({"axe"}));
	set_adj("sawed-off");
	add_adj("halberd");
	set_short("sawed-off halberd head");
	set_long("Once a halberd whose spear tip had broken, it has had its "
	+ "haft sawed down and wrapped with black hemp cloth so it can be "
	+ "wielded as an axe.  Its blade is in fair shape and is holding a "
	+ "very sharp edge.\n");

	set_hit(26);
	set_pen(32);
	set_wt(W_AXE);
	set_dt(W_SLASH);
	set_hands(W_ANYH);
}

