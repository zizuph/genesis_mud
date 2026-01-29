
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(24);
    set_name("wine");
    add_name("glass");
    set_adj("glass of");
   
    set_short("glass of wine");
    set_pshort("glasses of wine");
    set_long("It is a glass of wine.\n");
    add_prop(OBJ_I_WEIGHT, 230);
    add_prop(OBJ_I_VOLUME, 230);
}

