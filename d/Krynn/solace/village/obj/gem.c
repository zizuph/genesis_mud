/* Gem */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    //moves = 0;

    set_name(({"gem", "sla_mori_gem"}));
    set_adj("green");
    set_short("Green gem");
    set_long("Green gem.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 10);
}
