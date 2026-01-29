/* Ashlar, 20 Oct 97 */

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define ARMOUR_CLASS    22

void
create_armour()
{
    set_name("shield");
    add_name("buckler");
    set_adj("black");
    add_adj("crescent-marked");
    add_adj("crescent");
    add_adj("marked");
    set_short("black crescent-marked shield");
    
    set_ac(ARMOUR_CLASS);
    set_at(A_SHIELD);
    set_long("The " + short() + " is a round shield made of metal. " +
    "It is painted black and the face is covered by a crescent-shaped " +
    "indentation.\n");

    add_prop(OBJ_I_VOLUME, 2200);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ARMOUR_CLASS, A_TORSO));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));
}

