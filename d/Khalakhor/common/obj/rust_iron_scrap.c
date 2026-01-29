/*
 * rust_iron_scrap
 *
 * Just a scrap of rusty iron, maybe someone can find
 * something useful for it in the future ;)
 *
 * Khail - Dec 14/97.
 */
#pragma strict_types

#include <stdproperties.h>

inherit "/std/object";

public void
create_object()
{
    set_name("scrap");
    add_name("iron");
    set_adj("rusty");
    add_adj("iron");
    set_long("This twisted little scrap of iron appears " +
        "to have been left exposed to the elements for " +
        "quite some time, it's badly rusted, and " +
        "completely worthless.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 100);
}
