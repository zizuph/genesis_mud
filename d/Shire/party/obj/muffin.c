inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
    set_name("muffin");
    set_adj(({"blueberry","yummy"}));
    set_short("yummy blueberry muffin");
    set_long("A fist-sized muffin stuffed with succulent "+
      "blueberries.\n");
    set_amount(35);
    add_prop(HEAP_I_UNIT_WEIGHT, 40);
    add_prop(HEAP_I_UNIT_VOLUME, 40);

    add_prop(HEAP_S_UNIQUE_ID,"_party_muffin");
}
