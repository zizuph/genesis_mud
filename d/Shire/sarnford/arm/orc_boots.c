/*
 * Orc mail - Sarn Ford
 * Varian - February 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("boots");
    set_pname("boots");
    set_short("studded, leather boots");
    set_long("These leather boots are covered with metal studs to help " +
        "provide some additional protection to your feet. The leather " +
        "itself seems to be cracked and worn, but you think the boots " +
        "can be servicable for the next little while anyhow.\n");
    	    
    add_adj("studded");
    add_adj("leather");
    
    set_at(A_FEET);
    set_ac(1);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
