/*
 * Belt in Mirkwood
 * Varian - June 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("belt");
    set_pname("belts");
    set_short("worn, leather belt");
    set_long("This is an old, worn belt which has certainly seen better " +
        "days. However, not only is the belt still functional, it has a " +
        "pouch attached to the side where you could perhaps store a few " +
        "coins. \n");
    	    
    add_adj("worn");
    add_adj("leather");
    
    set_at(A_WAIST);
    set_ac(1);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
