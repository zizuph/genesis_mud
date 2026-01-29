/* Mortis 02.2006
 *
 * Common shield worn by city guards in Palanthas.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../local.h"

#define VK_NOBUY                    "_vkeep_shop_no_buy"

void setup_gear();

public void
create_armour()
{
	set_name("shield");
	set_adj("marble-centered");
	add_adj(({"steel"}));
	set_short("marble-centered steel shield");
	set_long("This small, shield has a strap keeping it close to the "
	+ "forearm, and a wooden handle to hold onto and maneuver it.  "
	+ "A translucent white, marble stone hemisphere is set into the "
	+ "shield's center, symbolic of the Palanthas city guard.\n");

	set_at(A_SHIELD);

	set_alarm(0.5, 0.0, "setup_gear");
}

void
setup_gear()
{
	set_ac(20 + random(2));
	set_am(({2, -1, -1}));

	add_prop(OBJ_I_VOLUME, 2700 + random(1350));
	add_prop(OBJ_I_WEIGHT, 2800 + random(1800));
	add_prop(OBJ_I_VALUE, 250 + random(100));
	add_prop(VK_NOBUY, 1);
}