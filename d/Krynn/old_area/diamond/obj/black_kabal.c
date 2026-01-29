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
    set_name("kabal");
    add_name("shot");
    set_adj("black");
    set_short("shot of black Kabal");

    set_long("This famous liquor from Kabal is known to have a kick "+
    "as strong as a horse! It looks very thick and creamy, and is dark "+
    "of color. The fumes of its potency can be detected from several "+
    "feet away. It was made in honor of the great Kabal himself, hero "+
    "of humanity.\n");
    set_drink_msg("You knock back the black Kabal in one gulp!\n");

    add_prop(HEAP_I_UNIT_WEIGHT, 170);
    add_prop(HEAP_I_UNIT_VOLUME, 150);
}
