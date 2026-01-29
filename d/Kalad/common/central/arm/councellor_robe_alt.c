/* 
 * /d/Kalad/common/central/arm/councellor_robe.c
 * Purpose    : The high lords councellors robe
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * 
 * Modified as an alternative when the main is not cloned.
 */ 

/*
robe worn by The High Lords councellor
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Kalad/defs.h"

create_armour()
{
   ::create_armour();

   set_name("robe");
   set_adj("large");
   add_adj("comfortable");
   set_long("This large robe covers the body of the wearer and gives some "+
      "protection. It looks comfortable.\n");

   set_ac(20);
   set_at(A_ROBE);

   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,2000);
}

