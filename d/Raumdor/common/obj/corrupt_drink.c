/* 2017-09-03 Malus: Creating replacement for rot/foul effect */ 
#include "defs.h"
inherit "/std/drink";

void
create_drink()
{
    set_name(({"_raumdor_corrupt_drink", "container", "liquid"}));
    set_adj("fouled");
    set_short("container of fouled liquid");
    set_pshort("containers of fouled liquid");
    add_prop(OBJ_I_VALUE, 0);
}

public mixed
command_eat()
{
    return "That is fouled an undrinkable.\n";
}
