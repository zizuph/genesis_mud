inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Korat */
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("grey");
   add_adj("decorated");
   set_long("This robe is decorated with long, thin silver threads that "+
      "curles together on the back, making out the form of a silver dragon. You are "+
      "struck by the beauty of it.\n");
   set_ac(4);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 1500);
}
