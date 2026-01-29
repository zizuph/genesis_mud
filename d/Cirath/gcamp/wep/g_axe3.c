inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("axe");
   set_adj("bone-handled");
   add_adj("iron-bladed");
   set_long("The bone of a large animal forms the shaft of this "
   	+"axe.  Nestled atop the bleached white bone rests a large "
   	+"piece of iron, cleverly shaped into the killing wedge "
   	+"of an axe.  It is obviously sharp, just eyeing the edge "
   	+"tells you that much.  It also is very hot to the touch, "
   	+"probably the result of the blackened iron soaking up the "
   	+"sun's rays.\n");
   set_hit(40);
   set_pen(34);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,8500);
   add_prop(OBJ_I_VOLUME,3000);
}

