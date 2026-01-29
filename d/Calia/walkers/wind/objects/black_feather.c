
inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

create_heap()
{
    set_name("feather");
    add_name("black feather");
    add_pname("feathers");
    add_pname("black feathers");
    set_short("black feather");
    set_pshort("black feathers");
    set_long("It's a small black feather.  It looks like it "+
        "might have come from a crow.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,0);
    add_prop(HEAP_I_UNIT_WEIGHT,0);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "black feather");
}
