
inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

create_heap()
{
    set_name("salt");
    add_name("white crystals");
    set_short("handful of white crystals");
    set_pshort("handfuls of white crystals");
    set_long("This handful of white crystals is salt.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,0);
    add_prop(HEAP_I_UNIT_WEIGHT,0);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "salt");
}
