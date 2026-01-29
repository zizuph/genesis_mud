/*
 * Box for holding donated items
 * 
 * Finwe, January 2001
 */

inherit "/std/container";
#include <stdproperties.h>

public void
create_container()
{
    set_short("large iron box");
    set_name("box");
    set_adj("iron");
    set_long("This is a large rectangular iron box used to " +
        "store weapons, armours, and other items for the guild.\n");

    add_prop(OBJ_M_NO_GET, "The iron box is too heavy to take.");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  50000);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

}
