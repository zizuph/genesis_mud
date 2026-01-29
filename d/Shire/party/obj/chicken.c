inherit "/std/food";

#include <stdproperties.h>

void
create_food()
{
    set_name("chicken");
    set_adj(({"whole","roast","roasted","stuffed"}));
    set_short("whole roast chicken");
    set_long("A whole chicken, stuffed with currants and mushrooms, slowly "+
      "wood-roasted until its skin is golden-brown.\n");
    set_amount(600);
    add_prop(HEAP_I_UNIT_WEIGHT, 800);
    add_prop(HEAP_I_UNIT_VOLUME, 900);

    add_prop(HEAP_S_UNIQUE_ID,"_party_chicken");
}
