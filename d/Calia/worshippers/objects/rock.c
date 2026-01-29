
inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

create_heap()
{
    set_name("small rock");
    add_name("rock");
    set_short("small rock");
    set_pshort("small rocks");
    set_long("A small rock.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,50);
    add_prop(HEAP_I_UNIT_WEIGHT,50);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "rock");
}
