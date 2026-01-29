inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("tequila");
    add_name("shot of tequila");
    set_short("shot of tequila");
    set_long("It's strong but tolerable.\n");

    set_soft_amount(50);   /* shot */
    set_alco_amount(30);   /* 60% alcohol */
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,50);
    add_prop(OBJ_I_VALUE,90);
    /* suggested price: 90cc */
}
