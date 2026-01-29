inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
create_armour()
{
   ::create_armour();
   set_name("robe");
   set_adj("thick");
   set_long("This is a thick robe that some of the guards wear as "
	+"protection. It seems to be lined with leather as added "
	+"protection.\n");
   set_ac(15);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,220);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
