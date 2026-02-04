inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
set_name(({"helmet", "war-helm","helm","armor","armour"}));
set_adj("black");
set_short("black war-helm");
set_long(
"A black war-helm, carved with ornate serpents.\n");
set_ac(16);
set_at(A_HEAD);
set_am(({0, 0, 0}));
add_prop(OBJ_I_WEIGHT, 700);
add_prop(OBJ_I_VOLUME, 850);
/* add_prop(OBJ_I_VALUE, comp_value(15)); */
}
