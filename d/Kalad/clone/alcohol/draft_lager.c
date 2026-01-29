inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("draft lager");
    add_name("lager");
    add_name("cup of lager");
    add_name("cup of draft lager");

    set_long(BS("It's a 12 ounce cup of draft lager. You suspect the "+
       "bartender watered it quite a bit.\n"));

    set_soft_amount(340);   /* 12 ounces */
    set_alco_amount(10);   /* 3% alcohol */
    add_prop(OBJ_I_WEIGHT,340);
    add_prop(OBJ_I_VOLUME,340);

    /* suggested price: 30cc */
}
