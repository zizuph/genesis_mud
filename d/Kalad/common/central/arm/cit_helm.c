/* 
 * /d/Kalad/common/central/arm/cit_helm.c
 * Purpose    : The citadel-guards helmet
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
Guard/Eliteguards/Officers tabard helm
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
   set_name("helm");
   set_adj("grey");
   add_adj("tabard");
   set_long("This is a well made tabard helm that will cover your head "+
      "against most hits, being constructed by sheets "+
      "of steel and fitted with a noseguard. You notice an engraving of a "+
       "clenched fist on the frontpart, marking this as an armour worn by the "+
      "Guards of the High Lord of Kabal.\n");
   set_ac(20);
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE,150);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,2000);
}

