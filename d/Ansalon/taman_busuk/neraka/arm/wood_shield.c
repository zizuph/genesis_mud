/* Ashlar, 21 Aug 97 */

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
    set_name("shield");
    set_adj("reinforced");
    add_adj("wooden");
    set_ac(ARMOUR_CLASS);
    set_at(A_SHIELD);
    set_short("reinforced wooden shield");
    set_long("This is a round shield made of wood, reinforced with metal " +
    "strips along the edges and in bands across the surface to give " +
    "better protection against blows.\n");

    add_prop(OBJ_I_VOLUME, 2200);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}
