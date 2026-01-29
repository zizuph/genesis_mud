inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("leather armour");
    add_name("armour");
    set_pname("armours");
    set_adj("leather");
    set_adj("studded");
    set_short("studded leather armour");
    set_pshort("studded leather armours");
    set_long(BSN("The studded leather armour is made of closely set metal "
      + "studs embedded in soft leather."));
    set_default_armour( 14, A_BODY, 0, 0);
    add_prop(OBJ_I_VALUE,  F_VALUE_ARMOUR(14)+random(100)-50);
    //add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(14, A_BODY)+random(100)-50);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
