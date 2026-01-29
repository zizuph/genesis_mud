/* 
 * /d/Kalad/common/wild/pass/wep/tcsword.c
 * Purpose    : A stone sword from Underdark
 * Located    : Used by some sword in Underdark?
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("large");
   add_adj("stone");
   add_adj("battle");
   set_long("A roughly-hewn stone sword crafted from the strange, dark "+
      "rock of the underdark. It looks like it could do a considerable "+
      "amount of damage.\n");
   set_hit(21);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,400);
   add_prop(OBJ_I_WEIGHT,12500);
   add_prop(OBJ_I_VOLUME,12500);
}
