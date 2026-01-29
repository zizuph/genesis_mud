inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name(({"hide","breastplate","armor","armour"}));
set_adj("leather");
set_short("leather hide");
set_long(
"A long hide of leather, with white fur.\n"
);
set_ac(15);
set_at(A_BODY);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 3500);
add_prop(OBJ_I_VOLUME, 3500);
/*add_prop(OBJ_I_VALUE, comp_value(10)); */
}
