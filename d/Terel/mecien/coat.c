inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_armour(){
   set_name(({"coat","breastplate","armor","armour"}));
   set_adj("leather");
   set_short("leather coat");
   set_long(
      "A very rigid leather coat.\n"
   );
   set_ac(10);
   set_at(A_BODY);
   set_am(({0, 0, 0}));
   add_prop(OBJ_I_WEIGHT, 9500);
   add_prop(OBJ_I_VOLUME, 9500);
}
