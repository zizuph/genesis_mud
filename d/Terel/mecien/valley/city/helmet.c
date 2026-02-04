inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name(({"helmet","helm","armor","armour"}));
set_adj("silver");
set_short("silver helmet");
set_long(
"A fine silver helmet with the crest of a raven.\n"
);
set_ac(20);
set_at(A_HEAD);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 1000);
add_prop(OBJ_I_VOLUME, 850);
/* add_prop(OBJ_I_VALUE, comp_value(15)); */
}
