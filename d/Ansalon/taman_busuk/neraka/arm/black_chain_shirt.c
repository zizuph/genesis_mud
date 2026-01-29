/* Ashlar, 20 Oct 97 */

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
    add_adj("blackened");
    add_adj("black");
    set_short("blackened chainmail shirt");
    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_long("The " + short() + " is crafted of the finest steel, " +
    "blackened, and decorated with a silver slash running across " +
    "the chest from the left shoulder to the right side of the waist. " +
    "The inside of the shirt is padded with cloth.\n");

    add_prop(OBJ_I_VOLUME, 2150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}

