/* Ashlar, 9 Jun 97 - a chainmail helm (hood) */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS    18

void
create_armour()
{
    set_name("hood");
    add_name("helm");
    set_adj("chainmail");
    add_adj("chain");
    add_adj("mail");
    set_short("chainmail hood");
    set_ac(18);
    set_at(A_HEAD);
    set_long("The hood is made of interwoven chains of steel on a soft " +
        "leather padding. It is more comfortable than a rigid helmet, but " +
        "offers less protection.\n");
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_HEAD) +
        random(50));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
    set_am(({-1,2,-1}));
}

