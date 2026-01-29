/* A leather armour for an insectoid.
 * Coded by Marisol (9/23/97)
 * Copyright (c) Marisol Ramos 1997 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    
    set_name("tunic");
    set_short("tattered tunic"); /* Observe, not 'a small helmet' */    
    set_long("It's a tattered leather tunic. No the best "+
    " protection, but is better than nothing at all.\n");

    set_adj("tattered");

    set_ac(10);

    set_am(({ -2, 1, 1 })); 

    set_at(A_BODY); 

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/1);
    add_prop(OBJ_I_VALUE,  100);
}                                                                     
