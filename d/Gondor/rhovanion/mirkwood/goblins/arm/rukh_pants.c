/*
 * Rukh's pants
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
    set_name("pair of pants");
    add_name("pants");
    set_pname("pairs of pants");
    set_short("dirty pair of pants");
    set_long("This dirty pair of pants appears to have been made of some " +
        "sort of cloth, although they are so heavily worn and stained that " +
        "you can no longer identify it any further.\n");
    	    
    add_adj("dirty");
    add_adj("cloth");
    
    set_at(A_LEGS);
    set_ac(10);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
