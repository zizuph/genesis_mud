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
    set_name("chainmail");
    set_pname("chainmails");
    set_short("worn, rusty chainmail");
    set_long("This suit of chainmail will cover your body, but it has " +
        "obviously seen much better days. The mail looks very worn, " +
        "with several links missing while most of the remaining " +
        "links are heavily rusted. The entire suit of armour has the " +
        "distinct stench of orc embedded in it.\n");
    	    
    add_adj("worn");
    add_adj("rusty");
    
    set_at(A_BODY);
    set_ac(15);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 7000);
    
}
