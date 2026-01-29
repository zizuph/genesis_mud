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
    set_short("grey, woolen shirt");
    set_long("This thick, heavy shirt has been made from grey wool. It looks " +
        "like it would keep you very warm, even through a cold evening. You " +
        "notice a strange fishy odour coming from the shirt however.\n");
    	    
    add_adj("grey");
    add_adj("woolen");
    
    set_at(A_BODY);
    set_ac(5);
    set_am(({ 4, 2, -6 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
