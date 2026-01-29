/*
 * Clyptas - July 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{ 

    set_name("boots");

    add_name("boots");

    set_short("black leather boots");

    set_adj("black");

    add_adj("leather");

    set_long("These are standard black boots with adamantine tips.\n");
    
    set_at(A_FEET);

    set_ac(20);

}