/*
 * Pants for Faelund
 * Varian - August 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("pants");
    set_pshort("pairs of pants");
    add_name("pair of pants");
    set_short("brown pair of pants");
    set_pshort("brown pairs of pants");
    set_long("These brown pants are made of a strong, sturdy fabric that " +
        "would probably keep your legs warm even during a cold, winter day.\n");
    	    
    add_adj("brown");
    
    set_at(A_LEGS);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
