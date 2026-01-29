inherit "std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include <macros.h>

create_armour()
{
   set_name("greaves");
   add_adj("blood-stained");
   add_adj("well-worn");
   set_short("pair of greaves");
   set_long("These greaves look like they have seen many battles"+
      ". They are covered in blood and have many dents in them.\n");
   
   set_ac(40);
   set_at(A_LEGS);
   set_am(({ -5, 1, 4}));
   
   add_prop(OBJ_I_VALUE, 1000);
   add_prop(OBJ_I_WEIGHT, 1500);
   add_prop(OBJ_I_VOLUME, 490);
}

query_recover()
{
   return MASTER+":"+query_arm_recover();
}
init_recover(arg)
{
   init_arm_recover(arg);
}
