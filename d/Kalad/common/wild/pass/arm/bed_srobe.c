/* 
 * /d/Kalad/common/wild/pass/arm/bed_srobe.c
 * Purpose    : Camel robe
 * Located    : Used by the Bedlams in the desert
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
   set_adj("cloud");
   add_adj("white");
   set_long("A loose-fitting and comfortable robe of the softest camel fibers, "+
      "it is perfectly suited for the climate within the Great Kalad Waste. "+
      "An image of a red sun has been sewn onto it.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_VOLUME,1500);
   add_prop(OBJ_I_WEIGHT,1500);
}
