/* 
 * /d/Kalad/common/central/arm/cit_plate.c
 * Purpose    : The elite citadel-guards platemail
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
Guard/Eliteguards/Officers fullplate
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
   set_name("fullplate");
   set_adj("grey");
   add_adj("banded");
   set_long("This is a well made fullplate armour that will cover your body "+
      "and arms against most hits, being constructed of overlapping plates "+
      "of steel. You notice an engraving of a clenched fist on the breastplates, "+
      "marking this as an armour worn by the Guards of the High Lord of "+
      "Kabal.\n");
   set_ac(30);
   set_at(A_TORSO | A_ARMS);
   add_prop(OBJ_I_VALUE, 490);
   add_prop(OBJ_I_WEIGHT,11000);
   add_prop(OBJ_I_VOLUME,8000);
}

