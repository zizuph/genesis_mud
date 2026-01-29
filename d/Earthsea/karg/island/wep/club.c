inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

#include "defs.h"

void create_weapon()
{
 set_name("club");
 add_name("weapon");
 set_adj("gleaming");
 add_adj("spiked");
 set_wt(W_CLUB);
 set_dt(W_BLUDGEON);
 set_pen(30);
 set_hit(35);
 set_hands(W_ANYH);

 add_prop(OBJ_I_WEIGHT,3000);
 add_prop(OBJ_I_VOLUME,3000);
 add_prop(OBJ_I_VALUE,1050);

 set_long("This is club used by kargish invaders. It is gleaming "+
   "white and has spikes upon it. You see sign of Karg empire on "+
   "the handle.\n");
}

