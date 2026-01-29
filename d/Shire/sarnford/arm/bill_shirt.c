/*
 * Shirt for Bill
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
    set_name("shirt");
    set_pname("shirts");
    set_short("rugged, stained shirt");
    set_long("This is just the sort of rugged shirt you would expect " +
        "a fisherman to wear, complete with multiple stains and a " +
        "distinct fishy smell that will not go away.\n");
    	    
    add_adj("rugged");
    add_adj("stained");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, -6 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
