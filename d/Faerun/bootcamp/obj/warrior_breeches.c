/*
 * Clyptas - July 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{ 

    set_name("breeches");

    add_name("breeches");

    set_short("black fitted breeches");

    set_adj("black");

    add_adj("fitted");

    set_long("These are standard black breeches, fitted " +
        "snug. Standard for most drow warriors.\n");
    
    set_at(A_LEGS);

    set_ac(20);

}