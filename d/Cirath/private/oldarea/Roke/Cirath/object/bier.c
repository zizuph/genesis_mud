inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(4);
    set_name("bier");
    set_adj("german");
    set_short("german bier");
    set_pshort("german biers");
    set_long("This bier looks nice!\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
