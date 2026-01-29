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

    set_short("pair of high black boots");

    set_adj("high");

    add_adj("black");

    set_long("These boots are high, tight, soft  black leather boots lined " +
        "with rothe fur.\n");
    
    set_at(A_FEET);

    set_ac(20);

}