inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Korat */
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("white");
   add_adj("weighty");
   set_long("A large, heavy robe that will cover most of your body. "+
      "Embroided on it you see two swords that cross each other, but "+
      "except that there is no decorations on it.\n");
   set_ac(4);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME,1500);
}
