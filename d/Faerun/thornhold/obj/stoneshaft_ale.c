/* Stoneshaft Ale by Twire */

inherit "/std/drink";
#include <stdproperties.h>
void
create_drink()
{
    set_name("ale");
    set_short("Stoneshaft ale");
    set_adj("ale");
    set_long("A stout, golden ale with a bitter aroma.\n");
    set_soft_amount(100);
    set_alco_amount(15);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
