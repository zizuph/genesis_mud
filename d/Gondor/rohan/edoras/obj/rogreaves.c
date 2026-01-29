inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("greaves");
    set_pname("greaves");
    add_pname("greaveses");
    add_pname("greavess");
    set_adj(({"shining", "pair of", "splint", "mail"}));
    set_short("pair of shining greaves");
    set_pshort("pairs of shining greaves");
    set_long(BSN("These greaves are worn by the Rohirrim. " +
                 "They are made from splint mail. " +
                 "A white horse is emblazoned in them."));
    add_item(({"horse", "blazon"}), BSN(
        "Emblazoned onto the shining greaves is a running white horse, " +
        "taken from the coat of arms of Rohan."));
    set_default_armour(21,A_LEGS,({1,1,-2}),0);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(21) + random(300) - 150);
    add_prop(GONDOR_M_ROHIRRIM_NO_SELL, 1);
}

query_recover() { return MASTER+":"+query_arm_recover();}
init_recover(arg) {init_arm_recover(arg);}
