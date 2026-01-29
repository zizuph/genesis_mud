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
    set_name(({"armour", "greaves"}));
    set_pname("pairs of steel greaves");
    add_name("_ch_sgreaves_");
    set_short("pair of steel greaves");
    set_adj(({"polished","steel"}));
    set_long("This is a " + short() + ". They are scratched and have " +
        "been used in wars recently. The greaves are worn on the legs to " +
        "protect them during fights.\n");
    
    set_ac(AC);
    set_at(A_LEGS);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_M_NO_SELL, "This is a charity item, it cannot be sold.\n");
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC,A_BODY));
    add_prop(OBJ_I_VOLUME, F_VOLUME_ARMOUR);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC) +(random(200)));
    
}


