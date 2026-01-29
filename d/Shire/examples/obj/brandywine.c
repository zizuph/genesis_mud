inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(500);
    set_alco_amount(100);
    set_name(({"brandywine", "bottle"}));
    set_short("bottle of brandywine");
    set_long("A greyish bottle filled with Brandywine.\n");
    add_prop(HEAP_I_UNIT_VOLUME,500);
    add_prop(HEAP_I_UNIT_WEIGHT, 700);
    add_prop(HEAP_I_UNIT_VALUE, 120);
}
