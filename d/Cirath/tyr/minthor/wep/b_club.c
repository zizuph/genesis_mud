inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("cudgel");
   set_adj("hardwood");
   set_long("This club looks like it was designed more for "
	+"subduing prey than killing it, but it still looks "
	+"like it would pack a mean punch.\n");
   set_hit(35);
   set_pen(25);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}


