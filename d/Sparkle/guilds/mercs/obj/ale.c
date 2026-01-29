inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("ale");
    set_adj("light");
    set_short("light ale");
    set_pshort("light ales");
    set_long("An ordinary light ale.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
