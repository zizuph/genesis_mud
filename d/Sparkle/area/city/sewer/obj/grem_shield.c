/*
 * /d/Sparkle/area/city/sewer/obj/grem_shield.c
 *
 * This is the shield that some gremlins will wear. It is intended
 * to cover the the right arm and body.
 * 
 *
 * Created 22 FEB 2009, by Aeg (Matthew Morin)
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
    set_name("shield");
    add_name("feather-adorned suit", "leather suit");
    add_adj("feather-adorned");
    add_adj("leather");
    set_short("feather-adorned leather shield");
    set_long("This leather shield is crafted of hardened leather and it is "
           + "adorned with owlrat feathers. It is created with many owlrat "
           + "bones sewn into the leather.\n");
        
    set_ac(10 + random(5));
    set_at( A_SHIELD );
    set_am(({ 0, 2, -1 }));
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}
