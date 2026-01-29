/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/wep/bed_ssword.c
*   Modified by Meton - 2020
*  Goblin raiders stole weapons, Copied from:
*
* /d/Kalad/common/wild/pass/wep/bed_ssword.c
* Purpose    : A powerful scimitar sword used by the Bedlans
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
   set_name("scimitar");
   add_name("sword");
   set_adj("immense");
   add_adj("two-handed");
   add_adj("great");
   set_long("Surely this is the finest scimitar you've ever laid eyes "+
      "upon, for from its exquisitely balanced handle up along its graceful, "+
      "curving blade, the weapon is a masterpiece of craftsmanship and "+
      "style. The scimitar's hilt has been stylized into a red image of "+
      "the sun, rays of light emanating from it.\n");
   set_hit(27);
   set_pen(29);
   set_hands(W_BOTH);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,600);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
