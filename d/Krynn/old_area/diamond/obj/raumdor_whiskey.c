inherit "/std/drink";
#include "/d/Kalad/defs.h"
#pragma stricty_types

/* Sarr -  20.Mar.9 */
/* A drink, a black kabal */

void
create_drink()
{
    set_soft_amount(150);
    set_alco_amount(70);
    set_name("whiskey");
    add_name("shot");
    set_adj("raumdor");
    set_short("shot of Raumdor whiskey");

    set_long("This is a shot of the finest whiskey in Raumdor. Made "+
    "from the corn and rye of the fertile fields of Raumdor, it has "+
    "a potent kick. The earthy smell drifts up into your nose.\n");

    set_drink_msg("You wheeze out a long breath as you feel the whiskey go down your throat.\n");

    add_prop(HEAP_I_UNIT_WEIGHT, 170);
    add_prop(HEAP_I_UNIT_VOLUME, 150);
}
