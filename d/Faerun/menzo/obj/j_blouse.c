/*
 * Clyptas - July 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{ 

    set_name("blouse");

    add_name("blouse");

    set_short("white fitted blouse");

    set_adj("white");

    add_adj("fitted");

    set_long("This blouse is clean and white, the collar is large and " +
        "turned out. The cuffs are oversized and turned back.\n");
    
    set_at(A_TORSO);

    set_ac(20);

}