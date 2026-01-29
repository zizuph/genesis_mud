/* 
 * /d/Kalad/common/central/arm/cit_human_robe.c
 * Purpose    : The citizens robe (in the citadel)
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: 
 */ 

/*
General robe worn by humans in the citadel.
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
   switch(random(7))
   {
      case 0:
      set_adj("white");
      add_adj("dirty");
      break;
      case 1:
      set_adj("grey");
      add_adj("plain");
      break;
      case 2:
      set_adj("red");
      add_adj("decorated");
      break;
      case 3:
      set_adj("black");
      add_adj("simple");
      break;
      case 4:
      set_adj("green");
      add_adj("tarnished");
      break;
      case 5:
      set_adj("white");
      add_adj("elegant");
      break;
      case 6:
      set_adj("grey");
      add_adj("dirty");
      break;
      case 7:
      set_adj("black");
      add_adj("stained");
      break;
      case 8:
      set_adj("red");
      add_adj("luxurious");
      break;
   }

   set_long("This robe covers the body of the wearer and helps him or her "+
      "to keep the warmth.\n");
   set_ac(5);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,200);
   add_prop(OBJ_I_WEIGHT,2500);
   add_prop(OBJ_I_VOLUME,2000);
}

