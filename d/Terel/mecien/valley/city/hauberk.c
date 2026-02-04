inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name(({"chainmail","hauberk","chain","armor","armour"}));
set_adj("steel");
set_short("chain hauberk");
set_long(
"A well crafted chain hauberk, made of shining steel.\n"
);
set_ac(30);
set_at(A_BODY);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 10000);
add_prop(OBJ_I_VOLUME, 8500);
/* add_prop(OBJ_I_VALUE, comp_value(25)); */
}
