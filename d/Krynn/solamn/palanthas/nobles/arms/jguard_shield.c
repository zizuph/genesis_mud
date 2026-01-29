/* 
 * Shield worn by jeweler's guard in nobles quarter.
 *
 * Mortis 10.2006
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include "../../local.h"

public void
create_armour()
{
	set_name("shield");
	set_adj("steel-centered");
	add_adj(({"steel", "wooden"}));
	set_short("steel-centered wooden shield");
	set_long("This small, shield has a strap keeping it close to the "
	+ "forearm, and a wooden handle to hold onto and maneuver it.  "
	+ "A cap of battered steel is set over the shield's raised center "
	+ "increasing its strength.");

	set_at(A_SHIELD);

	set_ac(20 + random(3));
	set_am(({2, -1, -1}));

	add_prop(OBJ_I_VOLUME, 2650 + random(1250));
	add_prop(OBJ_I_WEIGHT, 2700 + random(1700));
	add_prop(OBJ_I_VALUE, 255 + random(120));
}
