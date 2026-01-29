inherit "/std/heap";

#include "../guild.h"
#include <stdproperties.h>
#include <macros.h>

string
crystal_long()
{
    return "The small clear crystal" + 
        ((num_heap() == 1) ? " is " : "s are ") + "completely " +
        "transparent and slightly luminescent.\n";
}

void
create_heap()
{
    set_heap_size(1);

    set_name(({ "crystal", CRYSTAL_OBJECT }));
    set_adj(({ "small", "clear" }));

    set_long(crystal_long);

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(HEAP_S_UNIQUE_ID, "kot_ri_crystal");

    add_prop(HEAP_I_UNIT_WEIGHT, 5);
    add_prop(HEAP_I_UNIT_VOLUME, 3);
    add_prop(HEAP_I_UNIT_VALUE, 20);
}    

void
init_arg(string arg)
{
    set_heap_size(atoi(arg));
}

string
query_auto_load()
{
    return MASTER + ":" + num_heap();
}
