inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
  set_name("cloak");
set_adj("wool");
set_long(
  "A simple well made cloak.\n");
set_ac(5);
set_at(A_ROBE);
set_am(({0, 0, 0}));
/* add_prop(OBJ_I_VALUE, comp_value(15)); */
}
