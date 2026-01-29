/* 
 * /d/Kalad/common/central/arm/patrol_robe.c
 * Purpose    : Robe worn by the watchmaker
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
robe worn by The High Lords councellor
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
   set_name("robe");
   set_adj("grey");
   add_adj("large");
   set_long("This heavy and weather-beaten robe still "+
      "is able to keep your body protected against the "+
      "hurls of cold, biting wind.\n");
   set_ac(3);
   set_at(A_BODY);
    add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2000);
}

