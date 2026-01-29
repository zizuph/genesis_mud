inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(20);
    set_name("wine");
    set_adj("sweet");
    set_short("sweet wine");
    set_pshort("sweet wines");
    set_long("It has a deep red colour and smells wonderful.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
