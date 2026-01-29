/*
 * Clyptas - July 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{ 

    set_name("hat");

    add_name("hat");

    set_short("large purple hat");

    set_adj("purple");

    add_adj("large");

    set_long("This wide-brimmed purple hat is adorned with a huge diatryma" +
        "feather set at a jaunty angle.\n");
    
    set_at(A_HEAD);

    set_ac(20);

}
