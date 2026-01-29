inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("amber ale");
    add_name("halfmoon amber ale");
    add_name("halfmoon");
    add_name("bottle of halfmoon");
    add_name("bottle of amber ale");
    add_name("bottle of halfmoon amber ale");

    set_short("bottle of amber ale");

    set_long(BS("It's a 12 ounce bottle of Halfmoon Amber Ale, "+
       "a favorite import in Kabal.\n"));

    set_soft_amount(340);   /* 12 ounces */
    set_alco_amount(17);   /* 5% alcohol */
    add_prop(OBJ_I_WEIGHT,340);
    add_prop(OBJ_I_VOLUME,340);

    /* suggested price: 51cc */
}
