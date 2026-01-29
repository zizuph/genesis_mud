inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("midnight");
   add_adj("black");
   set_long("A robe made of the darkest and finest material you have "+
      "ever laid eyes upon.\n");
   set_ac(2);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_I_VOLUME,2000);
   add_prop(OBJ_I_WEIGHT,2000);
}
