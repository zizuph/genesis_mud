/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/arm/
*   Eaten by wolves for loot.
*   Copied from: 
* 
 * /d/Kalad/common/wild/pass/arm/bed_erobe.c
 * Purpose    : A cloth robe
 * Located    : Used by the Bedlans in the desert
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("aba");
   add_name("robe");
   set_adj("bleach");
   add_adj("white");
   set_long("A loose-fitting robe that is perfectly suited to a life "
      + "within the intense heat of the Great Kalad Waste. An image of a "
      + "red sun has been sewn onto it.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,180);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_WEIGHT,1500);
}
