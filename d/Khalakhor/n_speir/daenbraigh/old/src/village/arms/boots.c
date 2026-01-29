/*
 * Goblin village - smith's boots
 * TAPAKAH, 09/2005
 */

#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       

#include "../../village/village.h"

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{   
    set_name("boots");
    set_pname("boots");

    set_adj("thick-soled");
    set_adj("leather");

    set_short("thick-soled leather boots");
    set_pshort("thick-soled leather boots");

    set_long("These smith boots are made of sturdy leather with thick soles "+
	     "and seem to provide quite a good defense from the heat of "+
	     "smithy's floor.");

    set_ac(V_ACLASS);
    set_at(A_LEGS);
    set_am(({0,0,0}));

    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(V_ACLASS));

}
