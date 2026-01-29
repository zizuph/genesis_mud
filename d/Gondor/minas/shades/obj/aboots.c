inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_armour() {
    set_name("boots");
    set_adj("black");
    set_adj("sleek");
    set_short("pair of black boots");
    set_long(BSN("These are nicely made sleek black leather boots. They " +
                 "look very comfortable and well broken in."));
    set_default_armour(20,A_FEET | A_ANKLES,({0,0,0}),0);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,700);
    add_prop(OBJ_I_VALUE,200);
}
