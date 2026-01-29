inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("packet of peanuts");
    set_pshort("packets of peanuts");
    set_name("peanut");
    set_pname("peanuts");
    set_adj("some");
    set_long("\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 220);
    set_amount(200);
}

