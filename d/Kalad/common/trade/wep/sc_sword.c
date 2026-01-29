inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("two-handed");
   add_adj("adamantite");
   set_long("A weapon forged out of pure adamantite, one of, if not the "+
      "strongest of metals known to human and demihuman kind. Emblazoned "+
      "upon the blade is the icon of a red hawk, the symbol of the "+
      "sheriff-captain of Kabal.\n");
   set_hit(32);
   set_pen(32);
   set_hands(W_BOTH);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VOLUME,9000);
}
