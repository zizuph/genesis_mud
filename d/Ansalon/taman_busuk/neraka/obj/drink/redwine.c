
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(24);     // nominal value 68 cc
    set_name("wine");
    add_name("glass");
    set_adj("red");
    add_adj("glass of");
   
    set_short("glass of red wine");
    set_pshort("glasses of red wine");
    set_long("It is a glass of red wine of nondescript making.\n");
    add_prop(OBJ_I_WEIGHT, 230);
    add_prop(OBJ_I_VOLUME, 230);
}

