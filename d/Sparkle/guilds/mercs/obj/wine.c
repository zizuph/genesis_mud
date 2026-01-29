inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(20);
    set_name("wine");
    set_adj("red");
    set_short("red wine");
    set_pshort("red wines");
    set_long("It has a deep red colour and smells wonderful.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
