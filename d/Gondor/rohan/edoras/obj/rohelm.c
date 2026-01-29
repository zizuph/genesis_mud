inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name(({"helm","helmet"}));
    set_pname("helms");
    add_pname("helmets");
    set_short("light steel helm");
    set_pshort("light steel helms");
    set_adj(({"rohirrim", "light", "steel"}));
    set_long(BSN("The helm is made of light steel, with a long nose-guard " +
        "in front. From the top of the helm as a crest flows a " +
        "white horse-tail. Helms of this kind are worn by the " +
        "soldiers of Rohan."));
    set_default_armour(20,A_HEAD,({ -1, 1, 0}),0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_HEAD) +
        random(500) - 250);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(400)-200);
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
