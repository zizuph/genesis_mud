/* Ashlar, 15 Jul 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS 3

void
create_armour()
{
    set_name("boots");
    add_name("pair");
    set_pname("boots");
    add_pname("pairs");
    add_pname("armours");
    set_adj("soft");
    add_adj("leather");
    add_adj("pair");
    add_adj("pairs");
    add_adj("of");
    set_short("pair of soft leather boots");
    set_pshort("pairs of soft leather boots");
    set_ac(ARMOUR_CLASS);
    set_at(A_FEET);
    set_long("The soft leather boots are pretty comfortable for walking " +
        "in, but they do not offer much protection against blows.\n");
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_FEET));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
    set_am(({0,0,0}));
}

