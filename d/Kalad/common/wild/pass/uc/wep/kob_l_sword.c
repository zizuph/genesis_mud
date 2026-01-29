inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <wa_types.h>
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("filthy");
   add_adj("long");
   set_long("A rather plain long sword that is in relatively good upkeep. "+
      "Its pommel appears to have once had a gem set in it, but is now "+
      "only occupied by a lackluster rock. There are a few stains composed of "+
      "feces on the sword's pommel.\n");
   set_hit(25);
   set_pen(23);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,6000);
}
