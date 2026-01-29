
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(5);
    set_name("ale");
    set_adj("outlander");
   
    set_short("mug of outlander ale");
    set_pshort("mugs of outlander ale");
    set_long("It is a fairly refreshing mug of ale.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
