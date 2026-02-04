inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name("fur");
set_adj("heavy");

set_long("A massive fur, white and gray. It has ringlets so it\n"
+"can be worn over the shoulders.\n");
set_ac(26);
set_at(A_ROBE);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT,10000);
add_prop(OBJ_I_VOLUME, 10000);
}
