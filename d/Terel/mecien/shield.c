inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name("shield");
set_adj("silver");

set_short("silver shield");
set_long("A strange runed silver shield.\n");
set_ac(10);
set_at(A_SHIELD);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 2000);
add_prop(OBJ_I_VOLUME, 6000);
/*add_prop(OBJ_I_VALUE, comp_value(10)); */
}
