/*
Citadel guards spear/trident/glaive
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon()
{
   ::create_weapon();
   switch (random(3))
   {
      case 0:
      set_name("hammer");
      set_adj("large");
      break;
      case 1:
      set_name("sledgehammer");
      set_adj("long");
      break;
      case 2:
      set_name("shovel");
      set_adj("plain");
      break;
      default:
      set_name("chisel");
      set_adj("small");
      break;
   }
   set_long("Its a plain tool used to build roads and the funament "+
      "of buildings.\n");
   set_hit(8);
   set_pen(18);
   set_wt(W_CLUB);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_BOTH);
   add_prop(OBJ_I_VALUE,100);
   add_prop(OBJ_I_WEIGHT,6500);
   add_prop(OBJ_I_VOLUME,6500);
}

