inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("sword");
   set_adj("razor-reed");
   add_adj("long");
   set_long("This sword appears to be made from a large "
	+"flexible reed.  Upon examination you notice that "
	+"it is incredibly sharp, sharp enough to shave with "
	+"if it actually came down to that.  It is a strange "
	+"silvery-blue color and instead of a traditional hilt "
	+"it has some hide wrapped around it so it can be held "
	+"without cutting the wielder.\n");
   set_hit(27);
   set_pen(32);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}

