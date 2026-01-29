inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

#include "defs.h"

void create_weapon()
{
 set_name("spear");
 add_name("weapon");
 set_adj("long");
 add_adj("war");
 set_wt(W_POLEARM);
 set_dt(W_SLASH|W_IMPALE);
 set_pen(32);
 set_hit(35);
 set_hands(W_ANYH);

 add_prop(OBJ_I_WEIGHT,2100);
 add_prop(OBJ_I_VOLUME,2100);
 add_prop(OBJ_I_VALUE,1200);

 set_long("This spear used by kargish officers. It looks long and "+
    "well balanced. You see sign of karg empire on the handle.\n");
}

