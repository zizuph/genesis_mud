inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();
   set_name("dagger");
   set_adj("bloodcrystal");
   add_adj("kris-bladed");
   set_short("kris-bladed bloodcrystal dagger");
   set_long("This dagger, is made from a stange crystaline "+
   "substance, known a Bloodcrystal. An eerie blood-red hue "+
   "eminates from its wicked cris blade.\n");
   set_hit(20);
   set_pen(20); /* This is bloodcrystal, very fine quality */
   set_wt(W_KNIFE);
   
}
