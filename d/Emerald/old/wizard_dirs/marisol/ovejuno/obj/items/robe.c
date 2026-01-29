
/* A leather armour for an insectoid.
 * Coded by Marisol (9/23/97)
 * Copyright (c) Marisol Ramos 1997 */
/* Used by Gorgi in the village of Ovejuno in Emerald.*/


inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{

    set_name("robe");
    set_short("simple robe"); 
    set_long("It's a simple robe. Gorgi was never fond of "+
        "fancy clothes.\n");

    set_adj("simple");

    set_ac(30);

    set_am(({ -2, 1, 1 }));

    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/1);
    add_prop(OBJ_I_VALUE,  100);
}                                   
