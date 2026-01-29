/* Mortis 02.2006
 *
 * Common weapons used by merchant house Trusq guards in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("mace");
	add_name(({"heavy"}));
	set_adj("iron-balled");
	set_short("heavy iron-balled mace");
	set_long("The mace has a long, leather wrapped handle topped with a "
	+ "heavy, studded iron ball.\n");

	set_hit(27);
	set_pen(34);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_BOTH);
}

