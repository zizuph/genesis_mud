/*
 * Urguk's shirt
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
    set_name("shirt");
    set_pname("shirts");
    set_short("yellow silk shirt");
    set_long("This yellow shirt is made of the finest silk!\n");
    	    
    add_adj("yellow");
    add_adj("silk");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, -6 }));
    
    add_prop(OBJ_I_VALUE, 3000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
