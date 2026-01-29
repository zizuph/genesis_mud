inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
create_armour()
{
   ::create_armour();
   set_name("cloak");
   set_adj("fur-lined");
   set_long("This is a cloak lined with fur that is worn by the guards "
	+"from Zhentil Keep to protect them from the weather.\n");
   set_ac(15);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,220);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
