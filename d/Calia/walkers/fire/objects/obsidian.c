
inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

create_heap()
{
    set_name("obsidian");
    add_name("black rock");
    add_name("rock");
    add_pname("rocks");
    set_short("black rock");
    set_pshort("black rocks");
    set_long("This black rock is obsidian.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,0);
    add_prop(HEAP_I_UNIT_WEIGHT,0);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "obsidian");
}
