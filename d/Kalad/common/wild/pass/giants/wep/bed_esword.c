/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/wep/bed_esword.c
*   Modified by Meton - 2020
*  Goblin raiders stole weapons, Copied from:
*
 * /d/Kalad/common/wild/pass/wep/bed_esword.c
 * Purpose    : A great steel sword used by the Bedlans
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
   set_adj("great");
   add_adj("steel-bladed");
   set_long("A massive sword, nearly as large as a two-handed sword. Its "+
      "blade is curved in a large crescent, perfect for slashing and "+
      "impaling an enemy. An image of a red sun has been engraved into "+
      "the leather pommel.\n");
   set_hit(20);
   set_pen(26);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,600);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
