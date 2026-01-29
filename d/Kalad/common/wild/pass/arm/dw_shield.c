/* 
 * /d/Kalad/common/wild/pass/arm/dw_shield.c
 * Purpose    : A small buckler of drow make
 * Located    : Used by the drows in Undreath
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("buckler");
   set_adj("adamantine");
   set_long("A buckler shield made of solid adamantine, it seems to be "+
      "more than enough protection for your arm.\n");
   set_ac(15);
   set_at(A_SHIELD);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_WEIGHT,1500);
   add_prop(OBJ_I_VOLUME,1500);
}
