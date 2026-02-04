inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name("shirt");
set_adj("chainmail");

set_long("A massive shirt of iron chainmail.\n");
set_ac(33);
set_at(A_BODY);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 24000);
add_prop(OBJ_I_VOLUME, 50000);
}
