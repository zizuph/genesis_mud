inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
create_armour()
{
   ::create_armour();
   set_name("helmet");
   set_adj("pot");
   set_long("This is a helmet that strongly resembles a pot.\n");
   set_ac(15);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE,220);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_WEIGHT,1000);
}
