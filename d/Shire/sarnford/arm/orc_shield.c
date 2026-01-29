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
    set_name("shield");
    set_pname("shields");
    set_short("round, wooden shield");
    set_long("This small, wooden shield is reasonably round, with an iron " +
        "edge that covers the rim of the shield. The shield is covered in " +
        "various nicks and cuts, but the leather straps that hold it to " +
        "your arm are in good condition. A shield like this would be an " +
        "effective tool in battle.\n");
    	    
    add_adj("round");
    add_adj("wooden");
    
    set_at(A_SHIELD);
    set_ac(15);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
