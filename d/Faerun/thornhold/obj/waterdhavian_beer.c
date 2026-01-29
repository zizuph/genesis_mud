/* Waterdhavian beer by Twire */

inherit "/std/drink";
#include <stdproperties.h>
void
create_drink()
{
    set_name("beer");
    set_short("Waterdhavian beer");
    set_adj("Waterdhavian");
    set_long("A weak, watered-down beer from Waterdeep.\n");
    set_soft_amount(100);
    set_alco_amount(5);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
