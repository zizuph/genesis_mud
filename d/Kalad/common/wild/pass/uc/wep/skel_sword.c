inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("old");
   add_adj("steel");
   set_long("An extremely old sword of steel. It is a testament to the "+
      "crafter of this weapon that it is still in one piece, for the "+
      "sword seems to have seen battle quite often. A faded symbol of a "+
      "dark sun is visible on what's left of its pommel.\n");
   set_hit(29);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
}
