inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("whiskey");
    add_name("shot of whiskey");

    set_short("shot of whiskey");
    set_long("Strong stuff! You know what to do.\n");

    set_soft_amount(50);   /* shot */
    set_alco_amount(40);   /* 80% alcohol */
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,50);
    add_prop(OBJ_I_VALUE,120);
    /* suggested price: 120cc */
}
