/*
 * A mink pelt
 * -- Finwe, Oct, 2007
 */

inherit "/std/object";
#include "/d/#include "/d/Gondor/defs.h"
/defs.h"
#include <stdproperties.h>

void
create_object()
{

    add_name(({"pelt"}));
    set_short("brown mink pelt");
    add_adj("brown");
    add_adj("mink");
    set_long("This is a " + query_short()+". It is brown and luxuriant " +
        "looking, and valued by furriers for its fur. It can probably " +
        "be sold and turned into something useful.\n");

    add_prop(OBJ_I_WEIGHT, 400+random(100));
    add_prop(OBJ_I_VOLUME, 25);
    add_prop(OBJ_I_VALUE, 200);
}
