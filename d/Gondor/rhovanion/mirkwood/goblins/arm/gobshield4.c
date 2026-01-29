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
    set_short("oval wooden shield");
    set_adj(({"oval", "wooden", }));
    set_long("This long shield is roughly oval shaped. A handful of iron " +
        "studs have been mounted in the middle of the shield, but " +
        "otherwise, the shield looks rather unremarkable.\n");
    	        
    set_at(A_SHIELD);
    set_ac(32);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_WEIGHT, 3000);
    
}
