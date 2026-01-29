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
	set_name("warhammer");
	add_name(({"hammer"}));
	set_adj("marble-blocked");
	add_adj(({"iron-handled", "marble"}));
	set_short("marble-blocked iron-handled warhammer");
	set_long("Atop a short length of iron with a molded grip and iron ball "
	+ "pommel is a eight inch long, beaked block of translucent white "
	+ "marble.  It has been afixed with a thin band of iron and, though it "
	+ "appears deadly, marble is not known for its combat durability.\n");

	set_hit(34);
	set_pen(40);

	set_likely_dull(11); // Increased chance to dull.
	set_likely_break(15); // Marble is much more likely to break and shatter.

	set_wt(W_CLUB);
	set_dt(W_BLUDGEON);
	set_hands(W_ANYH);

	add_prop(OBJ_I_VOLUME, 4400 + random(500));
	add_prop(OBJ_I_WEIGHT, 5000 + random(550));
	add_prop(VK_NOBUY, 1);
}

