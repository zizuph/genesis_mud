/* Mortis 02.2006
 *
 * Common weapons used by city guards in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include "../local.h"

#define VK_NOBUY                    "_vkeep_shop_no_buy"

create_weapon()
{
	set_name("shortsword");
	add_name("sword");
	set_adj("wide-bladed");
	add_adj("double-edged");
	set_short("wide-bladed double-edged shortsword");
	set_long("Wide of blade with a forward curving hilt to protect the "
	+ "fingers, this shortsword is double-edged and recently sharpened.  "
	+ "It is standard issue among the city guards of Palanthas.\n");

	set_hit(26);
	set_pen(23);
	set_wt(W_SWORD);
	set_dt(W_IMPALE | W_SLASH);
	set_hands(W_ANYH);

	add_prop(OBJ_I_VOLUME, 3000 + random(500));
	add_prop(OBJ_I_WEIGHT, 4000 + random(550));
	add_prop(VK_NOBUY, 1);
}

