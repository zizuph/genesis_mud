
inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

create_heap()
{
    set_name("feather");
    add_name("spotted feather");
    add_pname("feathers");
    add_pname("spotted feathers");
    set_short("spotted feather");
    set_pshort("spotted feathers");
    set_long("It's a small spotted feather.  It looks like it "+
        "might have come from a seagull.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,0);
    add_prop(HEAP_I_UNIT_WEIGHT,0);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "spotted feather");
}
