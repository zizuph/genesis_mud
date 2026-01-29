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
    set_name("helm");
    set_pname("helms");
    set_short("dented, iron helm");
    set_long("This helmet seems to be a little scratched and dented on " +
        "the surface, but the padding inside seems to be in more or less " +
        "good condition, if you don't mind the stench of orc that is.\n");
    	    
    add_adj("dented");
    add_adj("iron");
    
    set_at(A_HEAD);
    set_ac(13);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(13));
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 200);
    
}
