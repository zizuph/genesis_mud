inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("poleaxe");
    set_pname("poleaxes");
    set_short("large poleaxe");
    set_pshort("large poleaxes");

    set_adj("large");

    set_default_weapon(12, 17, W_POLEARM, W_BLUDGEON | W_SLASH, W_BOTH);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12, 17) + 100 - random(50));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(17, W_POLEARM) + 500 - random(250));
  
    set_long(BSN("The "+ query_name() +" is made of a long wooden pole topped "+
        "with a wide bladed axe head that is backed by a heavy, rounded hammer "+
        "head."));
}

