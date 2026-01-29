
inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

create_heap()
{
    set_name("ash");
    add_name("grey powder");
    add_name("powder");
    add_pname("powders");
    set_short("handful of grey powder");
    set_pshort("handfuls of grey powder");
    set_long("This handful of grey powder is ash.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,0);
    add_prop(HEAP_I_UNIT_WEIGHT,0);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "ash");
}
