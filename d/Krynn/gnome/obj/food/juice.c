inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(0);
    set_name("juice");
    set_adj("gnomish");
    set_short("can of juice");
    set_pshort("cans of juice");
    set_long("Stored in little metal cylinders for convenience. What a concept...\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
