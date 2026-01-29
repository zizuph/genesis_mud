/* Mortis 03.2006
 *
 * Enchanted war chain wielded by Giae, High Guard of
 * merchant house Trusq in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../../local.h"

create_weapon()
{
	set_name("mace-axe");
	add_name(({"mace", "axe", "maceaxe"}));
	set_adj("iron-balled");
	set_short("iron-balled mace-axe");
	set_long("The mace-axe has a short, leather wrapped handle topped with a "
	+ "heavy iron ball.  Two inches of axe blade protrude from the axe "
	+ "running from its tip to shaft.  Though wielded as a mace, it can "
	+ "deliver chops and slashes similar to an axe.\n");

	set_hit(28);
	set_pen(30);
	set_wt(W_CLUB);
	set_dt(W_BLUDGEON | W_SLASH);
	set_hands(W_ANYH);

	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	add_prop(MAGIC_AM_ID_INFO, ({"\n", 20}));
    add_prop(MAGIC_AM_MAGIC,({25, "enchantment"}));
	add_prop(OBJ_S_WIZINFO, "\n");
}

