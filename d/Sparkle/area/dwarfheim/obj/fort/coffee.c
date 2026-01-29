#pragma strict_types
#pragma save_binary

inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(200);
    set_name("coffee");
    set_adj("dwarven");
    set_short("small amount of dwarven coffee");
    set_pshort("dwarven coffees");
    set_long("It looks as black and as thick as tar. This is real coffee.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

