inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name("shield");
set_adj("iron");

set_long("A large, crude, iron shield.\n");
set_ac(32);
set_at(A_SHIELD);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 27000);
add_prop(OBJ_I_VOLUME, 6000);
/*add_prop(OBJ_I_VALUE, comp_value(10)); */
}
