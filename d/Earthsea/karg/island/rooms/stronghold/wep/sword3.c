inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

#include "defs.h"

void create_weapon()
{
 set_name("broadsword");
 add_name("sword");
 add_name("weapon");
 set_adj("gleaming");
 add_adj("white");
 set_wt(W_SWORD);
 set_dt(W_SLASH);
 set_pen(28);
 set_hit(28);
 set_hands(W_ANYH);

 add_prop(OBJ_I_WEIGHT,3000);
 add_prop(OBJ_I_VOLUME,3000);
 add_prop(OBJ_I_VALUE,800);

 set_long("This is broadsword used by kargish officers. It has white "+
   "gleaming broad blade. You see sign of Karg empire on the handle.\n");
}

