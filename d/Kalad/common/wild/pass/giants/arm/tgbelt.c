/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/arm/
*   Modified by Meton - 2020
*   Eaten by wolves for loot.
*   Copied from:
*
 * /d/Kalad/common/wild/pass/arm/tgbelt.c
 * Purpose    : A belt
 * Located    : Goliath or Grumbar?
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("belt");
   set_adj("leather");
   set_long("Little more than a hardened strip of leather, this belt "
      + "offers little in the way of protection. Unremarkable stones have "
      + "been set into it.\n");
   set_ac(5);
   set_at(A_WAIST);
   add_prop(OBJ_I_VALUE,120);
   add_prop(OBJ_I_WEIGHT,250);
   add_prop(OBJ_I_VOLUME,250);
}
