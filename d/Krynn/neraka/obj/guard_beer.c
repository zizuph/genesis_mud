inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink() {
    set_soft_amount(100);
    set_alco_amount(5);
    set_name("beer");
    add_name("guard_beer");
    set_short("beer from Guardians Pub");
    set_pshort("beers from Guardians Pub");
    set_long("The beer is dark and it smells terrific. You feel like drinking " +
	 "it at once.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(HEAP_S_UNIQUE_ID, "guard_beer");
}
