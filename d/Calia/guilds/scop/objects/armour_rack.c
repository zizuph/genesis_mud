
/* 
 *  Armour rack for the Spirit Circle of Psuchae
 *  July 29th, 2003
 *
 *  Petros - September 2008
 *   - Changed to use the describable rack system.
 */

inherit "/d/Genesis/specials/guilds/objs/armour_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

#include "defs.h"

void
create_rack()
{
    set_name("rack");
    add_name("armour rack");
    add_name("arack");
    set_adj("armour");
    add_adj("large");
    set_short("large armour rack");
    set_long("This large armour rack is made from polished metal and look "+
        "like it might hold alot of sets of armour. If you wanted, you "+
        "could kick it to remove things that will not save. <kick armour "+
        "rack>\n"); 

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The large armour rack can't be taken, it is "+
        "entirely too heavy.\n");
}
