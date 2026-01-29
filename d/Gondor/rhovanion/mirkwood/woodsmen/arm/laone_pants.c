/*
 * Pants for Laone
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
    set_short("rough pair of pants");
    set_pshort("rough pairs of pants");
    set_long("This pair of pants is rather rough and coarse. They are " +
        "probably very good for long treks through the forest as you " +
        "suspect most thorns and brambles would be unable to tear them.\n");
    	    
    add_adj("rough");
    
    set_at(A_LEGS);
    set_ac(8);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
