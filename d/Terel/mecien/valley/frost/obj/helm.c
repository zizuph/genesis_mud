inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name("helm");
set_adj("horned");

set_long("A large, crude, iron shield.\n");
set_ac(18);
set_at(A_HEAD);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 8000);
add_prop(OBJ_I_VOLUME, 13000);
}
