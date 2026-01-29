/* 
 * /d/Kalad/common/central/arm/cit_boots.c
 * Purpose    : The citadel-guards boots
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
Eliteguards/Officers combat boots
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/armour.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

create_armour()
{
   ::create_armour();
   set_name("boots");
   set_pname("boots");
   set_adj("grey");
   add_adj("combat");
   set_long("This is a well made pair of combat boots that will cover your legs "+
      "against most hits, being constructed by vertical strips of metal riveted "+
      "to a hard leather. You notice an engraving of a "+
      "knitted fist on the sides of them, marking this as an armour worn by the "+
      "Guards of the High Lord of Kabal.\n");
   set_ac(12);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE, 150);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2000);
}

