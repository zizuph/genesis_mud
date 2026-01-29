/* 
 * /d/Kalad/common/wild/pass/arm/dw_helm.c
 * Purpose    : Adamantine helm of drow make
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
   set_name("helmet");
   set_adj("adamantine");
   set_long("An open-faced helm of extremely fine adamantine, it looks to "+
      "have been excellently forged, giving it an incredible sturdiness.\n");
  set_ac(18);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE,350);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
