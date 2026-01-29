/* Mortis 02.2006
 *
 * Heavy boots worn by city guards in Palanthas.
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
	set_name("boots");
	set_adj("studded");
	add_adj(({"grey"}));
	set_short("pair of studded grey boots");
	set_pshort("pairs of studded grey boots");
	set_long("Common issue boots for guardsmen, they are grey leather with "
	+ "white-enameled iron studs.\n");

	set_alarm(0.5, 0.0, "setup_gear");
}

void
setup_gear()
{
	set_ac(8);
	set_am(({1, -1, 0}));
	set_at(A_FEET);

	add_prop(OBJ_I_VOLUME, 2700 + random(1350));
	add_prop(OBJ_I_WEIGHT, 2800 + random(1800));
	add_prop(OBJ_I_VALUE, 70 + random(50));
	add_prop(VK_NOBUY, 1);
}