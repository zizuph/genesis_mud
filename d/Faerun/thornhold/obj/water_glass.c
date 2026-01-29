/* Stoneshaft Ale by Twire */

inherit "/std/drink";
#include <stdproperties.h>
void
create_drink()
{
    set_name("water");
    set_short("glass of water");
    set_adj("glass");
    set_long("A glass of plain water.\n");
    set_soft_amount(100);
    set_alco_amount(0);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
