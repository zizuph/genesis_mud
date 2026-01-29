/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/wep/bed_espear.c
*   Modified by Meton - 2020
*  Goblin raiders stole weapons, Copied from:
*
* /d/Kalad/common/wild/pass/wep/bed_espear.c
* Purpose    : A spear used by the Bedlans
* Located    : The Bedlans in the desert
* Created By : Antharanos  ??.??.??
* Modified By: 
* First Modif: 
*/ 

inherit "/d/Kalad/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("spear");
   set_adj("large");
   add_adj("steel-tipped");
   set_long("A hefty wooden shaft with a triangular-shaped tip fashioned "+
      "from forged steel. An image of a red sun has been carved into its "+
      "shaft.\n");
   set_hit(22);
   set_pen(16);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
