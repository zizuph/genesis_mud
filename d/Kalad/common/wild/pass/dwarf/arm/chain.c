inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
/* by korat */
create_armour()
{
   ::create_armour();
   set_name("chainmail");
   set_adj("heavy");
   set_long("This chainmail, made of hardened leather with a "+
      "layer of heavy metal-chains upon it has seen better days "+
      "but will still do its job in protecting your body.\n");
   set_ac(15);
   set_at(A_TORSO);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_VOLUME, 4000);
   add_prop(OBJ_I_WEIGHT, 4000);
}
