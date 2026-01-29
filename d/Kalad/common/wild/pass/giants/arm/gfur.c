/* 
* /d/Kalad/common/wild/pass/giantpass/arm/gfur.c
* Purpose    : Giant fur coat
* Located    : Used by the giants in the redwood
* Created By : Antharanos ??.??.??
* Modified By: Meton 2020
*/ 

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("fur");
   set_adj("giant");
   set_long("This huge fur must belong to a giant, because it is so "
      + "huge. It seems to have been crafted from the coats of lions, "
      + "wolves and bears.\n");
   set_ac(5); // We say its about as strong as leather due to its bulk
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE, 200);
   add_prop(OBJ_I_WEIGHT,25000);
   add_prop(OBJ_I_VOLUME,15000);
}
