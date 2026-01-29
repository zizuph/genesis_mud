
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(90);
    set_alco_amount(30);    // nominal value 100 cc
    set_name("vingaard");
    add_name("glass");
    add_name("rocks");
    set_adj("small");

    set_short("small glass of 'Vingaard under rocks'");
    set_pshort("small glasses of 'Vingaard under rocks'");

    set_long("The drink consists of a clear oily liquid chilled by " +
        "small pieces of ice.\n");
   
    add_prop(OBJ_I_WEIGHT, 110);
    add_prop(OBJ_I_VOLUME, 120);
}

