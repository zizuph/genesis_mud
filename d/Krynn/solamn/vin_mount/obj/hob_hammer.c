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
	set_name("hammer");
	set_adj("narrow-tipped");
	add_adj("iron");
	set_short("narrow-tipped iron hammer");
	set_long("A handheld warhammer in design, it is too small to inflict "
	+ "heavy blows.  Its wooden handle is unsanded, and the iron used in its "
	+ "small head is so narrow it is almost as likely to pierce as crush.\n");

	set_hit(18);
	set_pen(14);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);
}
