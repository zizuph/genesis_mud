/* 
 * Low quality hammer used by hobgoblins in a cave
 * along the road south of Palanthas.
 *
 * Mortis 10.2006
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../local.h"

create_weapon()
{
	set_name("sword");
	set_adj("iron");
	add_adj("grut");
	set_short("iron grut sword");
	set_long("Costing little to produce in quantity and requiring even less "
	+ "skill, the grut sword is a cast iron weapon wielded similarly to a "
	+ "sword but with a thin, flat edge to its iron blade.  Commonly found "
	+ "among warbands of hobgoblins, it is more feared than their hammers "
	+ "for its pinpoint smashing abilities.  Wrapped tightly around its hilt "
	+ "is a thin piece of leathered skin.\n");

	set_hit(17);
	set_pen(21);
	set_wt(W_SWORD);
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);
}
