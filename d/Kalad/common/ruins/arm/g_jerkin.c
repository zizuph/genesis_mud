inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
create_armour()
{
   ::create_armour();
   set_name("jerkin");
   set_adj("leather");
   set_long("This is a plain leather jerkin that some of the guards "
	+"wear. It seems durable, but not all that durable.\n");
   set_ac(15);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,220);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
