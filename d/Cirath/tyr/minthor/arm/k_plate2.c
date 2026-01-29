inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("breastplate");
   add_name("plate");
   set_adj("shimmering");
   add_adj("crystal");
   set_short("shimmering crystal breastplate");
   set_long("A breastplate unlike one you have ever seen, it seems "
	+"to be made of a crystal that shimmers with rainbow colors "
	+"in the light.  You are unsure of where something like this "
	+"could have been created, but it is surely a work of art.\n");
   set_ac(45);
   set_at(A_BODY);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(OBJ_I_WEIGHT,9000);
   set_wf(TO);
}

query_recover()
{
   return 1;
}


