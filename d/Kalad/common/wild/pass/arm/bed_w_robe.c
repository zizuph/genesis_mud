/* 
 * /d/Kalad/common/wild/pass/arm/bed_w_robe.c
 * Purpose    : Silk white robe
 * Located    : Used by the Bedlams in the desert
 * Created By : Antharanos ??.??.??
 * Modified By: 
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
   set_adj("frost");
   add_adj("white");
   set_long("A long, comfortable robe made of some silky fabric. Its "+
      "design helps keep its wearer relatively cool in the terrible heat "+
      "so common in the Great Kalad Waste.\n"+
      "A symbol of a red sun is on each of the robe's sleeves.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_VOLUME,1250);
   add_prop(OBJ_I_WEIGHT,1250);
}
