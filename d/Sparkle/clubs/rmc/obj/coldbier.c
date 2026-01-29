inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("beer");
    set_adj("cold");
    set_short("cold beer");
    set_long("This beer looks nice! And it is cold too!\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
