
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(6);     // nominal value 14 cc
    set_name("ale");
    add_name("mug");
   
    set_short("mug of ale");
    set_pshort("mugs of ale");
    set_long("It is a mug of ale.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

