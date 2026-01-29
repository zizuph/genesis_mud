
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>

create_armour(){
set_name(({"mail","chainmail","armor","armour"}));
set_adj("chain");
set_short("ghostly chainmail");
set_long(
"This chainmail is slightly luminescent, and has an unearthly quality.\n"
);
set_ac(25);
set_at(A_BODY);
set_am(({-1, 0, 1}));
add_prop(OBJ_I_WEIGHT, 1000);
add_prop(OBJ_I_VOLUME, 3000);
}
