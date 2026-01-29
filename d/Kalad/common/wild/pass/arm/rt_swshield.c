/* 
 * /d/Kalad/common/wild/pass/arm/rt_swshield.c
 * Purpose    : An old iron shield
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
   set_name("shield");
   set_adj("ancient");
   add_adj("iron");
   set_long("A round shield made of iron that bears the marks of extreme "+
      "age in its time-ravaged appearance.\n");
   set_ac(15);
   set_at(A_SHIELD);
   add_prop(OBJ_I_VALUE,180);
   add_prop(OBJ_I_VOLUME,2500);
   add_prop(OBJ_I_WEIGHT,2500);
}
