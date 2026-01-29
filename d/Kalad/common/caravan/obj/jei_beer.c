inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_drink()
{
    set_soft_amount(125);
    set_alco_amount(10);
    set_name("beer");
    set_adj("kabal");
    set_short("kabal beer");
    set_pshort("kabal beers");
    set_long("A dark brew favored by the citizens of Kabal.\n");
    add_prop(OBJ_I_WEIGHT,125);
    add_prop(OBJ_I_VOLUME,125);
}
