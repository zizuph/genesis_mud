/*
 * Clyptas - July 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{ 

    set_name("cape");

    add_name("cape");

    set_short("flowing iridescent cape");

    set_adj("flowing");

    add_adj("iridescent");

    set_long("This is a long, iridescent cape, beset with an obsidian stone" +
        "set at the clasp.\n");
    
    set_at(A_SHOULDERS);

    set_ac(20);

}
