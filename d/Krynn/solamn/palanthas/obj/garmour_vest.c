/* Mortis 02.2006
 *
 * Light chainmail vest worn by city guards in Palanthas.
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
	set_name("vest");
	set_adj("light");
	add_adj(({"chainmail"}));
	set_short("light chainmail vest");
	set_long("Very fine and small steel rings have been used in the "
	+ "construction of this vest keeping it light.  It is sleeveless "
	+ "with a V-neck for slipping it over your head.\n");

	set_alarm(0.5, 0.0, "setup_gear");
}

void
setup_gear()
{
	set_ac(30 + random(2));
	set_am(({1, 2, -3}));
	set_at(A_BODY);

	add_prop(OBJ_I_VOLUME, 4250 + random(350));
	add_prop(OBJ_I_WEIGHT, 5600 + random(400));
	add_prop(OBJ_I_VALUE, 400 + random(200));
	add_prop(VK_NOBUY, 1);
}