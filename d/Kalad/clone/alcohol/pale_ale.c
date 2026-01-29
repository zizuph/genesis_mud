inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("pale ale");
    set_adj("bottle of");
    add_adj("imported");

    set_long(BS("It's a 12 ounce bottle of pale ale. "+
       "It's probably imported.\n"));

    set_soft_amount(340);   /* 12 ounces */
    set_alco_amount(13);   /* 4% alcohol */
    add_prop(OBJ_I_WEIGHT,340);
    add_prop(OBJ_I_VOLUME,340);

    /* suggested price: 39cc */
}