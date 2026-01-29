/* by Mortis 10.2005
 *
 * Sir Engen's special leggings only he can wear
 * (because the left leg is fake and won't fit over
 * someone who has a left leg).
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "../../local.h"

#define VK_NOBUY                    "_vkeep_shop_no_buy"

void
create_armour()
{
    set_name("legs");
    set_pname("pairs of legs");
    set_adj("chain");
    add_adj("plate");
    set_short("chain armoured right legging and plate booted false left leg");
    set_pshort("pairs of chain armoured right leggings and plate booted false "
	+ "left legs");
    set_long("Held together by buckles and harnesses, this armour covers the "
	+ "right leg and left thigh in chainmail.  The left leg from the knee "
	+ "down is a false metal, plated leg and boot which can only be worn "
	+ "by someone missing their left leg.  The harness above the left leg "
	+ "is intended to be hooked to something above the waist.\n");

    set_ac(35);
    set_at(A_LEGS);
	set_af(TO);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(35));
	add_prop(VK_NOBUY, 1);
}

mixed
wear(object what)
{
	if (TP->query_prop(HAS_NO_LEFT_LEG) == 1 )
	{
		return 0;
	}

    return "There is no room for your left leg in this armour.\n";
}
