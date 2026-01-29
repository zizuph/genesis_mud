/* Ashlar, 21 Aug 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS    14

void
create_armour()
{
    set_name("shirt");
    set_adj("studded");
    add_adj("leather");
    set_short("studded leather shirt");
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_long("This is a shirt of thick leather with metal studs sewn " +
    "onto the leather. It is dirty and a bit torn along the edges.\n");

    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}

