inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* Mhyrkhaan */

void
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("short");
   add_adj("slim");
   set_short("slim short sword");
   set_long("This sword, is short and slim. It's edge is keen, and "+
   "looks capable of inflicting some nasty wounds.\n");
   set_hit(21);
   set_pen(16);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,1500);
}

