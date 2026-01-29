inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("boots");
   set_adj("studded");
   add_adj("leather");
   set_pshort("studded leather boots");
   set_long("An extremely large pair of leather boots that rise up to cover "+
      "the legs. Sharp metal studs cover the pair for added protection.\n");
   set_ac(15);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE, 360);
   add_prop(OBJ_I_VOLUME, 900);
   add_prop(OBJ_I_WEIGHT, 900);
}
