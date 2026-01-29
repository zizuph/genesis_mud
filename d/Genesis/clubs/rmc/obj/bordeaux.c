inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(10);
    set_name("bordeaux");
    set_adj("glass of");
    set_short("glass of bordeaux");
    set_pshort("glasses of bordeaux");
    set_long("This is a glass of red delicious bordeaux wine.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
