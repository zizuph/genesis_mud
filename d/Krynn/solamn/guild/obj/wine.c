inherit "/std/drink";
#include "/sys/stdproperties.h"

void
create_drink()
{
    set_soft_amount(200);
    set_alco_amount(20);
    set_name("wine");
    set_adj("imported");
    set_long("It both smells and tastes good.\n");
    set_short("imported wine");
    set_pshort("imported wines");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

