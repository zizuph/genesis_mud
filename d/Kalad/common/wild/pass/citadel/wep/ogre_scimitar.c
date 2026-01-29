/*
 * Made by Korat
 * September 1996
 * 
 * A scimitar wielded by a big ogre
 * 
*/
inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

create_weapon()
{
   ::create_weapon();
   set_name("scimitar");
   set_adj("long");
   add_adj("heavy");
   add_adj("iron");
   set_long("It is a rather long one-edged, curved sword that "+
      "will easily do "+
      "damage to those who gets in its way. Not of the best "+
      "metal in this world, but it does the job.");
   set_hit(28); /* removed 2 since it is so large */
   set_pen(25); /* added 4 since it is so large */
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_wf(TO);
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,5000);
}
