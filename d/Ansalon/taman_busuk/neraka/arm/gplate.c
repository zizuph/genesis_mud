/* Ashlar, 9 Jun 97 - a steel breastplate of the city guards */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 35

void
create_armour()
{
    set_name("breastplate");
    add_name("plate");
    set_adj("thick");
    add_adj("steel");
    add_adj("breast");
    set_short("thick steel breastplate");
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_long("The breastplate is made of thick steel, and decorated " +
        "in the manner of the City Guards of Neraka. It is padded with " +
        "leather on the inside.\n");
    add_prop(OBJ_I_VOLUME, 2600);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO) +
        560 + random(300));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
    set_am(({0,0,0}));
}

