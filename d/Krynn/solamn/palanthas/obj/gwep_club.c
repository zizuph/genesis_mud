/* Mortis 02.2006
 *
 * Common weapons used by city guard commanders in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../local.h"

#define VK_NOBUY                    "_vkeep_shop_no_buy"

create_weapon()
{
	set_name("clubber");
	add_name(({"club"}));
	set_adj("wood-handled");
	add_adj(({"hemp-bagged"}));
	set_short("wood-handled hemp-bagged clubber");
	set_long("Sewn to a wooden grip molded to fit the hand is a two "
	+ "foot long hemp bag packed tight with sawdust.  Commonly used "
	+ "by Palanthas city guards, anyone on the receiving end of one "
	+ "of these will be knocked senseless until subdued.\n");

	set_hit(25);
	set_pen(14);

	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);

	add_prop(OBJ_I_VOLUME, 4400 + random(500));
	add_prop(OBJ_I_WEIGHT, 4600 + random(550));
	add_prop(OBJ_I_VALUE, 175 + random(200));
	add_prop(VK_NOBUY, 1);
}
