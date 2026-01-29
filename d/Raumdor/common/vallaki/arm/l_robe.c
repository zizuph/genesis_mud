inherit "/std/armour";
#include "/d/Raumdor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_armour()
{
   ::create_armour();
   set_name("robe");
   set_short("old grey robe");
   set_adj("old");
   add_adj("grey");
   set_long("It is an old, grey robe made of soft cloth.\n");
   set_ac(1);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE, 10);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_WEIGHT, 500);
}
