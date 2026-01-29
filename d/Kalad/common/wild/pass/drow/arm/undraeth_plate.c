inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_adj("black");
   add_adj("adamantine");
   set_long("A highly-crafted and exquisitely forged suit of adamantine "+
      "plate armour. It is clearly of superior quality to even the best of "+
      "human-made armours.\n");
   set_ac(35);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE, 800);
   add_prop(OBJ_I_WEIGHT, 20000);
   add_prop(OBJ_I_VOLUME,12500);
}
