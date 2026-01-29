/*
 * Pants for Banor
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
    set_short("dirty pair of pants");
    set_pshort("dirty pairs of pants");
    set_long("This pair of pants seems to be rather dirty, but, you suppose " +
        "that they could be worn regardless.\n");
    	    
    add_adj("dirty");
    
    set_at(A_LEGS);
    set_ac(5);
    set_am(({ 4, 2, 0 }));
    
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
