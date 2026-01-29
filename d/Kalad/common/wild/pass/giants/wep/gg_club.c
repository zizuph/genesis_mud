/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/wep/gg_club.c
*   Modified by Meton - 2020
*  Goblin raiders stole weapons, Copied from:
*
 * /d/Kalad/common/wild/pass/wep/gg_club.c
 * Purpose    : A iron-spiked club of goblin make
 * Located    : Used by the Red Hand Goblins in the mountains
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
   set_name("club");
   set_adj("large");
   add_adj("iron-spiked");
   set_long("A large wooden club with many nasty iron spikes "+
      "protruding up and down its length. A bloody hand clutching an "+
      "eyeball has been painted on its handle.\n");
   set_hit(20);
   set_pen(17);
   set_wt(W_CLUB);
   set_dt(W_SLASH | W_BLUDGEON);
   add_prop(OBJ_I_VALUE, 400);
   add_prop(OBJ_I_WEIGHT,7500);
   add_prop(OBJ_I_VOLUME,7500);
}
