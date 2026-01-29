/* Ashlar, 9 Jun 97 - chainmail greaves */

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
    set_name("greaves");
    add_name("pair");
    set_pname("greaves");
    add_pname("pairs");
    add_pname("armours");
    set_adj("chainmail");
    add_adj("chain");
    add_adj("mail");
    set_short("pair of chainmail greaves");
    set_pshort("pairs of chainmail greaves");
    set_ac(18);
    set_at(A_LEGS);
    set_long("The greaves protect the legs of the wearer with a layer of chain " +
        "mail on soft leather.\n");
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_LEGS) +
        random(50));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
    set_am(({-1,2,-1}));
}

