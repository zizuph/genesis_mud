inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(355);
    set_alco_amount(20);
    set_name(({"beer", "bottle"}));
    set_short("bottle of beer");
    set_long("A bottle of good old Molson Canadian, eh.\n");
    set_drink_msg("You chug down the bottle of Molson Canadian with great speed.\n");
    add_prop(HEAP_I_UNIT_VOLUME,355);
    add_prop(HEAP_I_UNIT_WEIGHT, 400);
    add_prop(HEAP_I_UNIT_VALUE, 60);
}
