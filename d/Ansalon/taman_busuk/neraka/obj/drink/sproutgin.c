
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(160);
    set_alco_amount(35);     // nominal value 133 cc
    set_name("gin");
    add_name("glass");
    set_adj("sprout");
    add_adj("glass of");
   
    set_short("glass of sprout gin");
    set_pshort("glasses of sprout gin");
    set_long("It is a glass of gin made from the sprout, " +
        "believe it or not.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

