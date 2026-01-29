inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(20);
    set_name("cognac");
    set_adj("glass of");
    set_short("glass of cognac");
    set_pshort("glasses of cognac");
    set_long("This is a glass of aged cognac.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
