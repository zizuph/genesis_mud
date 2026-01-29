/* Ashlar, 21 Aug 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS    31

void
create_armour()
{
    set_name("mail");
    add_name("chainmail");
    add_name("shirt");
    set_adj("chain");
    add_adj("chainmail");
    set_short("chainmail shirt");
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_long("This is a shirt of chainmail armour, without any special " +
    "ornaments. It smells of goblin.\n");

    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}

