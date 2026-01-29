inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
    set_amount(300);
    set_name("steak");
    set_adj("juicy");
    set_short("steak");
    set_long("A thick, juicy steak.\n");

    add_prop(HEAP_I_UNIT_VOLUME, 300);
    add_prop(HEAP_I_UNIT_WEIGHT, 300);
    add_prop(HEAP_I_UNIT_VALUE, 200);
}
