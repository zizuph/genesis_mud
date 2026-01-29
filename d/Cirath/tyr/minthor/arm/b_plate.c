inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("breastplate");
   set_adj("heavy");
   add_adj("iron");
   set_short("heavy iron breastplate");
   set_long("Amazingly enough, this is an iron breastplate.  In Tyr "
	+"this is worth more than virtually any slave just by being "
	+"made of iron.  It looks like it will offer a good amount "
	+"of protection.  Over the heart you see a large capital M "
	+"denoting this as property of the Minthor House.\n");
   set_ac(35);
   set_am(({0,4,2}));
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT,200);
   add_prop(OBJ_I_VOLUME,200);
}

