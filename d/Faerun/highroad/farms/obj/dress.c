/*
 * Dress for missing girl quest
 * Finwe, August 2006
 */

#include "defs.h"
#include <stdproperties.h>
#include <composite.h>

inherit "/std/object";

create_object()
{
    set_name("dress");
    set_adj("ripped");
    set_adj("flora;");
    set_short("ripped floral dress");
    set_long("This is a " + short() + ". It has a bright floral pattern " +
        "but now has countless rips through it. The dress looks like " +
        "it was torn off a woman and discarded. Now, it looks like a pile " +
        "of worthless rags.\n");

    add_prop(OBJ_I_WEIGHT,   120);
    add_prop(OBJ_I_VOLUME,   500);
    add_prop(OBJ_I_VALUE,    250);

}
