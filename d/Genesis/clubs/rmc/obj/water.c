inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_name("water");
    set_adj("glass of");
    set_short("glass of water");
    set_pshort("glasses of water");
    set_long("This glass looks refreshing!\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
