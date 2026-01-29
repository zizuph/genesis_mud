/* 
 * /d/Kalad/common/wild/pass/arm/bed_robe.c
 * Purpose    : A robe used by the Bedlans
 * Located    : Used by the Bedlans in the desert
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("aba");
   add_name("robe");
   set_adj("light");
   add_adj("brown");
   set_long("A loose-fitting robe that is perfectly suited to a life "+
      "within the intense heat of the Great Kalad Waste. An image of a "+
      "red sun has been sewn onto it.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,120);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_WEIGHT,1500);
}
