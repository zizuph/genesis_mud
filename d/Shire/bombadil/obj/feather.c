/*
 * feather for Tom's hat. Obtained from pheasant corpse
 * -- Finwe, January 2002
 */

inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name(FEATHER_PROP);
    add_name(({"feather"}));
    set_short("golden pheasant feather");
    add_adj("golden");
    add_adj("pheasant");
    set_long("This "+short()+" is a tail feather. It is long and " +
        "pointed with a large black circle at the end. The feather " +
        "has a bluish and green iridescence and is a popular " +
        "feather for hats.\n");

    add_prop(OBJ_I_WEIGHT, 10); // Light as a feather, go figure
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 12);

}
