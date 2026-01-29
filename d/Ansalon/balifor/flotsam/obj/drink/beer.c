inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("beer");
    set_adj("small");
    set_short("small beer");
    set_pshort("small beers");
    set_long("It's a small but refreshing beer.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
