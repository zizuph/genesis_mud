inherit "/std/drink";

#include <stdproperties.h>

void
create_drink()
{
    set_name("wine");
    add_name("bottle");
    add_name("_Shire_bottle");
    set_adj(({"bottle","bottle of"}));
    set_short("bottle of white wine");
    set_pshort("bottles of wine");
    set_pname(({"bottles","wines","drinks"}));
    set_long("A large bottle of the finest white wine.\n");
    set_soft_amount(100);
    set_alco_amount(20);
    add_prop(HEAP_I_UNIT_WEIGHT, 300);
    add_prop(HEAP_I_UNIT_VOLUME, 200);

    add_prop(HEAP_S_UNIQUE_ID,"_forsaken_wine");
}
