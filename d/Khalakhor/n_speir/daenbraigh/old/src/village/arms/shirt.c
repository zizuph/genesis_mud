/*
 * Goblin village - a shirt
 * TAPAKAH, 04/2005
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
    set_name("shirt");
    set_pname("shirts");

    set_adj("rough");
    set_adj("woolen");

    set_short("rough woolen shirt");
    set_pshort("woolen shirts");

    set_long("This shirt is rough and made of thick wool, and looks to be "+
	     "quite warm and protective.\n");

    set_ac(V_ACLASS);
    set_at(A_ROBE);
    set_am(({-2,-2,-1}));

    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(V_ACLASS));

}
