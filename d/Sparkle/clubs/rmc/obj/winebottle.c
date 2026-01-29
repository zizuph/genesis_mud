inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(750);
    set_alco_amount(100);
    set_name("champagne");
    set_adj("pink");
    add_adj("bottle of");
    set_short("bottle of pink champagne");
    set_pshort("bottles of pink champagne");
    set_long("This is a bottle of pink champagne, perfect for outdoor meals.\n");
    add_prop(OBJ_I_WEIGHT, 750);
    add_prop(OBJ_I_VOLUME, 750);
}
