
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(20);     // nominal value 50 cc
    set_name("punch");
    add_name("cup");
    set_adj("plum");
   
    set_short("cup of plum punch");
    set_pshort("cups of plum punch");
    set_long("The plum punch, chilled, looks very refreshing.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

