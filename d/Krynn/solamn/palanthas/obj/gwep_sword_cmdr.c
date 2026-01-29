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
	set_name("sabre");
	add_name("sword");
	set_adj("marble-pommeled");
	add_adj("single-edged");
	set_short("marble-pommeled single-edged sabre");
	set_long("A long, slightly curving blade of steel extends from the hilt "
	+ "of this sabre.  The oval, brass hilt curves forward over the fingers "
	+ "for protection, and the handle is criss-cross wrapped with leather "
	+ "braids for grip.  Set into the brass-rimmed pommel is a counter "
	+ "balance sphere of polished, translucent white marble.\n");

	set_hit(36);
	set_pen(39);
	set_wt(W_SWORD);
	set_dt(W_IMPALE | W_SLASH);
	set_hands(W_ANYH);

	add_prop(OBJ_I_VOLUME, 2100 + random(500));
	add_prop(OBJ_I_WEIGHT, 2500 + random(550));
	add_prop(VK_NOBUY, 1);
}

