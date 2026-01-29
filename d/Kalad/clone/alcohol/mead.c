inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("warm mead");
    add_name("mead");
    add_name("tankard of mead");
    add_name("tankard of warm mead");
    add_name("tankard");

    set_short("tankard of warm mead");
    set_long(BS("It has a strong aroma and comes in a large "+
      "tankard with a handle that you can really grip.\n"));

    set_soft_amount(453);   /* a pint */
    set_alco_amount(23);   /* 5% alcohol */
    add_prop(OBJ_I_WEIGHT,453);
    add_prop(OBJ_I_VOLUME,453);

    /* suggested price: 69cc */
}
