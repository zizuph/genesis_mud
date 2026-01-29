/* 
 * /d/Kalad/common/wild/pass/wep/bed_m_sword.c
 * Purpose    : A giant two-handed curved sword, used by the Bedlans
 * Located    : The bedlans in the desert
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("scimitar");
   add_name("sword");
   set_adj("great");
   add_adj("two-handed");
   add_adj("red");
   set_long("A massive sword requiring both hands to even lift it. Its "+
      "great curving blade is the perfect weapon for cleaving the head "+
      "from someone's shoulders. An image of a red sun has been engraved "+
      "all over the blade, giving it the appearance of being bathed in "+
      "blood.\n");
   set_hit(29);
   set_pen(30);
   set_hands(W_BOTH);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,10000);
}
