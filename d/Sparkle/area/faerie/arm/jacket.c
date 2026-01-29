/*
 * Chainmail for elf guards
 * - Finwe, August 2004
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{

    set_name("armour");
    add_name("jacket");
    set_short("heavy leather jacket");
    set_adj("heavy");
    set_adj("leather");
    set_long("This is a " + short() + ". It is strong looking and protects " +
        "the torso. The leather has been hardened and offers some protection " +
        "during combat.\n");
    set_ac(5+random(5));
    set_at(A_TORSO);
    set_am(({0,1,-1}));
    
    add_prop(OBJ_I_VALUE, 250);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 3000);
}