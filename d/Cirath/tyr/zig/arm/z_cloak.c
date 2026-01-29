inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("cloak");
   set_adj("leather");
   add_adj("studded");
   set_short("studded leather cloak");
   set_long("Studded with pieces of obsidian and bone, "
   	+"this cloak will provide more protection than "
   	+"a regular cloak would.  The thick leather it "
   	+"is made from also provides protection, while "
   	+"the light tan color is ideal for desert "
   	+"concealment.\n");
   set_ac(5);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,70);
}

