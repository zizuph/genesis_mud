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
   switch (random(2))
   {
      case 0:
      set_name("trident");
      set_adj("large");
      set_hit(20);
      set_pen(20);
      set_dt(W_SLASH | W_IMPALE);
      break;
      case 1:
      set_name("spear");
      set_adj("long");
      set_hit(24);
      set_pen(16);
      set_dt(W_IMPALE);
      break;
      case 2:
      set_name("glaive");
      set_adj("broad");
      set_hit(17);
      set_pen(24);
      set_dt(W_SLASH | W_IMPALE);
      break;
   }
   set_long("This polearm has been taken well care of by its "+
      "former owner. Every inch of metal has been carefully waxed "+
      "and polished, making it shine. All the edges is sharp to the "+
      "touch, making this a good weapon. You see the symbol of the "+
      "High Lord of Kabal engraved "+
      "on the long shaft.\n");
   set_wt(W_POLEARM);
   set_hands(W_BOTH);
   add_prop(OBJ_I_VALUE, 350);
   add_prop(OBJ_I_WEIGHT,6500);
   add_prop(OBJ_I_VOLUME,6500);
}

