inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_adj("nice");
   set_long("A nice suit of platemail worn by the guards. It looks to "
	+"be able to offer some protection without being to "
	+"cumbersome.\n");
   set_ac(25);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,420);
   add_prop(OBJ_I_VOLUME,3000);
   add_prop(OBJ_I_WEIGHT,3000);
}
