inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name("mantle");
set_adj("silver");

set_short("silver mantle");
set_long("A beautiful silvery mantle, it seems to sparkle.\n");
set_ac(25);
set_at(A_ROBE);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 1000);
add_prop(OBJ_I_VOLUME, 2000);
/*add_prop(OBJ_I_VALUE, comp_value(25)); */
}
