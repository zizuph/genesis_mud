/* Created by Aridor, sometime in 1994
 *
 * this is a large bag which can be tied around the
 * body so that it won't be sold or dropped accidentally.
 */

inherit "/d/Krynn/solamn/thief/obj/bag";

#include <stdproperties.h>


void
create_bag()
{
    set_name("bag");
    set_adj("large");
    set_short("large bag");
    set_pshort("large bags");
    set_long("It's a large bag, and " +
	     "you can put quite some stuff into it.\n");
    add_prop(CONT_I_WEIGHT,     2500);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME,     1500);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 250);
    set_keep(1);
}
