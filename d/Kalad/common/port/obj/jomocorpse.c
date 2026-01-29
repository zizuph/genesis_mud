inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
/* by Antharanos */

create_object()
{
    set_short("corpse of a human");
    set_name("corpse");
    add_name("corpse of a human");
    add_name("human corpse");
    set_long("A dead body of a human being.\n");
    add_prop(OBJ_I_WEIGHT,30000);
    add_prop(OBJ_I_VOLUME,30000);
}
