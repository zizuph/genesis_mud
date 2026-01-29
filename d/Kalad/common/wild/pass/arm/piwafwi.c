/* 
 * /d/Kalad/common/wild/pass/arm/piwafwi.c
 * Purpose    : A grey cloak
 * Located    : Used by the drow in Undreath
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("piwafwi");
   add_name("cloak");
   set_adj("grey");
   set_long("An ash-grey cloak made of fibers so smooth and silky, it "+
      "would appear as if it were made out of silken spider webs.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_VOLUME,2000);
   add_prop(OBJ_I_WEIGHT,2000);
}
