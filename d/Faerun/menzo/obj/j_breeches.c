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

    set_short("crimson doe-skin breeches");

    set_adj("crimson");

    add_adj("doe-skin");

    set_long("These breeches are red as blood, dyed on the softest doe skin, fitted " +
        "snug.\n");
    
    set_at(A_LEGS);

    set_ac(20);

}