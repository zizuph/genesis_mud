inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("brown ale");
    add_name("hespyre brown ale");
    add_name("pint of brown ale");
    add_name("pint of hespyre");
    add_name("hespyre");
    add_name("pint of hespyre brown ale");

    set_short("pint of brown ale");
    set_long(BS("It's a pint of Hespyre Brown Ale, "+
       "brewed in the nearby Hespyre Mountains.\n"));

    set_soft_amount(453);   /* a pint */
    set_alco_amount(27);   /* 6% alcohol */
    add_prop(OBJ_I_WEIGHT,453);
    add_prop(OBJ_I_VOLUME,453);

    /* suggested price: 71cc */
}
