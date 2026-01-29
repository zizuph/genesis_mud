/*
 * Varian - February 5 2016
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
    set_short("small leather buckler");
    set_adj(({"small", "leather", }));
    set_long("This small buckler is made of leather stretched across a " +
        "circular iron frame. You don't imagine this would be much use " +
        "against any arrows, but it should be effective in melee combat.\n");
    	        
    set_at(A_SHIELD);
    set_ac(25);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 1000);
    
}
