#pragma strict_types

inherit "/std/armour";
#include "/d/Gondor/rohan/isengard/defs.h";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void create_armour() {
    set_name("brigandine vest");
    set_adj("light");
    set_short("light brigandine vest");
    add_name("vest");
    set_long(BSN("A vest of armour crafted from two light layers of "+
        "leather with plates of some hard material sandwiched between. It "+
        "bears the marks of the crafters of Isengard."));
    set_default_armour(22,A_TORSO,({1,1-2}),0);
    add_prop(ISEN_I_ARMOUR, 1);

}

