inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Korat */
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_adj("white");
   set_long("A plated armour that will protect your body from "+
      "damage. In the center of the suit you see an image engraved "+
      "upon it; a fist gripping a sword.\n");
   set_ac(30);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,960);
   add_prop(OBJ_I_VOLUME,10000);
   add_prop(OBJ_I_WEIGHT,10000);
}
