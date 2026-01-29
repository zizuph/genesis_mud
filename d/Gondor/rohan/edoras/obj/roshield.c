/* Shield of the Rohirrim */
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_short("green blazoned shield");
    set_pshort("green blazoned shields");
    set_adj(({"rohirrim", "blazoned", "green", "steel"}));
    set_long(BSN("This is a green shield of steel. Blazoned onto it " +
        "is the coat of arms of Rohan, a white running horse on a " +
        "green field. Only the soldiers of Rohan may wear this armour."));
    set_default_armour(25,A_SHIELD,({0,3,-3}),0);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(21) + random(300) - 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_SHIELD) +
        random(500) - 250);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

query_recover() { return MASTER+":"+query_arm_recover();}
init_recover(arg) {init_arm_recover(arg);}
