/*
 * Charity box armour
 * by Finwe, April 2005
 */

#include "defs.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
inherit "/std/armour";

#define AC 10 + random(15) + 1

create_armour()
{
    set_name(({"armour","helm","helmet"}));
    add_name("_ch_helm_");
    set_short("scratched steel helm");
    set_adj(({"ancient","steel"}));
    set_long("This is a " + short() + ". It has been through many battles " +
        "and has some large scratches on it.\n");
    
    set_ac(AC);
    set_at(A_HEAD);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC,A_BODY));
    add_prop(OBJ_I_VOLUME, F_VOLUME_ARMOUR);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC) +(random(600)-300));
    
}


