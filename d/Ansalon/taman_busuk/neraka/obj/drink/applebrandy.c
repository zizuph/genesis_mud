
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(100);
    set_alco_amount(40);     // nominal value 170 cc
    set_name("brandy");
    add_name("glass");
    set_adj("apple");
    add_adj("glass of");
    add_adj("small");
   
    set_short("small glass of apple brandy");
    set_pshort("small glasses of apple brandy");
    set_long("It is a small glass of apple brandy. The brandy is a " +
        "golden colour, and you guess it is quite strong.\n");
    add_prop(OBJ_I_WEIGHT, 120);
    add_prop(OBJ_I_VOLUME, 120);
}

