/*
 * Goblin village - smith's boots
 * TAPAKAH, 09/2005
 */
inherit "/d/Khalakhor/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../village/village.h"

void
create_khalakhor_armour()
{   
    set_name("boots");
    set_pname("boots");

    set_adj("thick");
    set_adj("leather");

    set_short("thick leather boots");
    set_pshort("thick leather boots");

    set_long(BSN("These smith boots are made of thick leather and seem to "+
		 "provide quite a good defense from the heat of smithy's floor.");

    set_ac(VACLASS);
    set_at(A_LEGS);
    set_am(({0,0,0}));

    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(VACLASS));

}
