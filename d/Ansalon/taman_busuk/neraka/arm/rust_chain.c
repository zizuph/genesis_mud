/* Ashlar, 21 Aug 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS    29

void
create_armour()
{
    set_name("mail");
    add_name("chainmail");
    set_adj("rusty");
    add_adj("chain");
    set_short("rusty chainmail");
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_long("This is a shirt of chainmail armour, heavily rusted " +
    "but well made.\n");

    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) - random(50));
}

