inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
create_armour()
{
   ::create_armour();
   set_name("shield");
   set_adj("steel");
   set_long("This is an ordinary steel shield that the guards use in "
	+"addition to their other armours.\n");
   set_ac(20);
   set_at(A_SHIELD);
   add_prop(OBJ_I_VALUE,220);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
