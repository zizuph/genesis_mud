inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("cloak");
   set_adj("well-worn");
   add_adj("thick");
   set_short("well-worn thick cloak");
   set_long("This is a thick, yet supple cloak made of some sort "
	+"of animal hide.  It is a deep black with swirling indigo "
	+"rings on it.  It hangs down to the back of the knees and "
	+"looks like it would confer a large amount of protection.\n");
   set_ac(5);
   set_at(A_ROBE);
  add_prop(OBJ_I_WEIGHT,1500);
   add_prop(OBJ_I_VOLUME,200);
}

