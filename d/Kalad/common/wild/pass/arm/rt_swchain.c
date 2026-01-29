/* 
 * /d/Kalad/common/wild/pass/arm/rt_swchain.c
 * Purpose    : An iron suit of chainmail, weak
 * Located    : Used by who knows
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("chainmail");
   set_adj("ancient");
   add_adj("iron");
   set_long("An suit of armour fashioned from iron that bears the "+
      "ravaging effects of time in its faded, weakened appearance.\n");
   set_ac(12);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,360);
   add_prop(OBJ_I_VOLUME,7500);
   add_prop(OBJ_I_WEIGHT,7500);
}
