/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/wep/tgaxe.c
*   Modified by Meton - 2020
*  Goblin raiders stole weapons, Copied from:
*
 * /d/Kalad/common/wild/pass/wep/tgaxe.c
 * Purpose    : A stone axe from the underdark
 * Located    : Used by some creature in the Underdark?
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
   set_name("axe");
   set_adj("stone");
   add_adj("battle");
   set_long("A roughly-hewn battle axed crafted from the strangely dark "+
      "rock of the underdark. It looks like it could do a considerable "+
      "amount of damage.\n");
   set_hit(21);
   set_pen(25);
   set_wt(W_AXE);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,360);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_WEIGHT,10000);
}
