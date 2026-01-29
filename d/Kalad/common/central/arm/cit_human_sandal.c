/* 
 * /d/Kalad/common/central/arm/cit_human_sandal.c
 * Purpose    : The citizens sandals (in the citadel)
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
General sandals worn by humans in the citadel.
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
   set_name("sandals");
   set_pname("sandals");
   switch(random(7))
   {
      case 0:
      set_adj("dirty");
      break;
      case 1:
      set_adj("plain");
      break;
      case 2:
      set_adj("mediocre");
      break;
      case 3:
      set_adj("grey");
      break;
      case 4:
      set_adj("normal");
      break;
      case 5:
      set_adj("unkempt");
      break;
      case 6:
      set_adj("ordinary");
      break;
      case 7:
      set_adj("nice");
      break;
      case 8:
      set_adj("standard");
      break;
   }

    set_pshort(query_adj() + " sandals");

   set_long("These sandals covers the feet of the wearer and helps him or her "+
      "to keep the warmth.\n");
   set_ac(3);
   set_at(A_FEET);
   add_prop(OBJ_I_VALUE,100);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
}

