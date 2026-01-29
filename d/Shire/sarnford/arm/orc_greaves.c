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
    set_name("greaves");
    set_short("thin, dented greaves");
    set_long("You are looking at a pair of thin, metal greaves. Dented " +
        "from heavy use over time, these greaves have leather straps " +
        "which wrap around your thighs to help protect your legs.\n");
    	    
    add_adj("thin");
    add_adj("dented");
    
    set_at(A_LEGS);
    set_ac(10);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
