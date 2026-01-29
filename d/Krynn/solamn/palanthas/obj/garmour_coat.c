/* Mortis 02.2006
 *
 * Heavy chainmail coat worn by city guards in Palanthas.
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
	set_name("coat");
	set_adj("heavy");
	add_adj(({"chainmail"}));
	set_short("heavy chainmail coat");
	set_long("Sturdy, double-steel rings have been used in the construction "
	+ "of this coat for added protection.  Long, chain sleeves extend to "
	+ "the wrists, and side straps keep the shirt buckled around the waist "
	+ "to prevent shifting.\n");

	set_alarm(0.5, 0.0, "setup_gear");
}

void
setup_gear()
{
	set_ac(33 + random(2));
	set_am(({1, 2, -3}));
	set_at(A_BODY | A_ARMS);

	add_prop(OBJ_I_VOLUME, 9400 + random(1350));
	add_prop(OBJ_I_WEIGHT, 9600 + random(1800));
	add_prop(OBJ_I_VALUE, 675 + random(250));
	add_prop(VK_NOBUY, 1);
}
