inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

#include "defs.h"

void create_weapon()
{
 set_name("waraxe");
 add_name("axe");
 add_name("weapon");
 set_adj("double");
 add_adj("bladed");
 set_wt(W_AXE);
 set_dt(W_SLASH);
 set_pen(30);
 set_hit(29);
 set_hands(W_ANYH);

 add_prop(OBJ_I_WEIGHT,4200);
 add_prop(OBJ_I_VOLUME,4200);
 add_prop(OBJ_I_VALUE,1000);

 set_long("This is waraxe used by kargish invaders. It has two "+
   "blades and looks well balanced. You see sign of karg empire "+
   "on the long handle.\n");
}

