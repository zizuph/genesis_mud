/*
 * /w/aeg/sparkle/sewer/obj/grem_suit.c
 *
 * This is the armour that some gremlins will wear. It is intended
 * to cover the the body and the legs.
 * 
 *
 * Created 11 FEB 2009, by Aeg (Matthew Morin)
 */
#pragma strict_types

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "../defs.h"

public void
create_armour()
{
    set_name("suit");
    add_name("feather-adorned suit", "leather suit");
    add_adj("feather-adorned");
    add_adj("leather");
    set_short("feather-adorned leather suit");
    set_long("This leather suit is crafted of hardened leather and it is "
           + "adorned with owlrat feathers. It is created with many joints "
           + "to allow unencumbered movement.\n");
        
    set_ac(20 + random(5));
    set_at( A_BODY | A_ARMS );
    set_am(({ 1, 3, 0 }));
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, 70));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}
