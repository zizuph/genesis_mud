/* 
 * /d/Kalad/common/wild/pass/wep/bed_spear.c
 * Purpose    : A strong spear used by the Bedlans
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
   set_adj("steel-tipped");
   set_long("A hefty wooden shaft with a triangular-shaped tip fashioned "+
      "from forged steel. An image of a red sun has been carved into its "+
      "shaft.\n");
   set_hit(23);
   set_pen(17);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,240);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2500);
}
