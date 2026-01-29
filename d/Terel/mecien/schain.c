inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name(({"chainmail","mail","chain","armor","armour"}));
set_adj("silver");
set_short("suit of silver chainmail");
set_long(
"This suit of silver chainmail is very old.\n"
);
set_ac(35);
set_at(A_BODY);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 5500);
add_prop(OBJ_I_VOLUME, 7500);
/*add_prop(OBJ_I_VALUE, comp_value(35)); */
}
