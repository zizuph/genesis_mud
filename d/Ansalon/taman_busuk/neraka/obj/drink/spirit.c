
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(220);
    set_alco_amount(45);    // nominal value 213 cc
    set_name("spirit");
    add_name("cup");
    set_adj("sword");

    set_short("cup of 'Sword Spirit'");
    set_pshort("cups of 'Sword Spirit'");

    set_long("It is a milky white liquid with tinges of blue. It looks " +
        "unhealthy.\n");
   
    add_prop(OBJ_I_WEIGHT, 220);
    add_prop(OBJ_I_VOLUME, 220);

    set_drink_msg("The Sword Spirit burns like red-hot blades down your " +
        "throat.\n");
}

