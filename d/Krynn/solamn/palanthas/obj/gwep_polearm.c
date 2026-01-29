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
	set_name("mancatcher");
	add_name(({"catcher", "polearm"}));
	set_adj("oak-shafted");
	add_adj("hook-toothed");
	set_short("oak-shafted hook-toothed mancatcher");
	set_long("Atop an eight foot oak shaft is a curving \"U\" shaped iron "
	+ "ring.  The open ring is lined with jagged, toothlike hooks for "
	+ "snaring and subduing opponents.\n");

	set_hit(28);
	set_pen(15);
	set_wt(W_POLEARM);
	set_dt(W_IMPALE);
	set_hands(W_BOTH);

	add_prop(OBJ_I_VOLUME, 3000 + random(500));
	add_prop(OBJ_I_WEIGHT, 4000 + random(550));
	add_prop(VK_NOBUY, 1);
}

