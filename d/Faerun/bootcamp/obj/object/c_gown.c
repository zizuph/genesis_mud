/*
 * Clyptas - July 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{ 

    set_name("gown");

    add_name("gown");

    set_short("silky cream-colored gown");

    set_adj("cream-colored");

    add_adj("silky");

    set_long("This is a long, cream colored silk gown. Held together by two " +
        "wide silver clasps at the shoulders.\n");
    
    set_at(A_TORSO);

    set_ac(20);

}
