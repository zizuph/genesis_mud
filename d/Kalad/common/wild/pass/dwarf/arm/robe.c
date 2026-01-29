inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
/* by korat */
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("large");
   set_long("This is a large robe of a black colour. You can "+
      "see some small holes in it, but are not sure wether it is "+
      "moles or swords that has made them.\n");
   set_ac(1);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE, 300);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_WEIGHT, 2000);
}
