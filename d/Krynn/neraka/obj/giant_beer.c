inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink() {
    set_soft_amount(100);
    set_alco_amount(5);
    set_name("beer");
    add_name("giant_beer");
    set_adj("dark");
    set_long("The beer looks very tasty, dark but clear.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(HEAP_S_UNIQUE_ID, "giant_beer");
}
