/*
 * /w/aeg/sparkle/sewer/obj/owlrat_pelt.c
 *
 * This is the armour that some gremlins will wear. It is intended
 * to be a cloak.
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
    set_name("pelt");
    add_name("feathery pelt", "owlrat pelt");
    add_adj("feathery");
    add_adj("owlrat");
    set_short("feathery owlrat pelt");
    set_long("This is a feathery owlrat pelt. It appears to have been cut "
           + "from the remains of an owlrat. It is a thick skin with dense "
           + "feathers attached. A rat tail trails off the bottom of this "
           + "pelt.\n");
        
    set_ac(10 + random(3));
    set_at( A_ROBE );
    set_am(({ 0, 2, 0 }));
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_ROBE));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}
