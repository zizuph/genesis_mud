inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("shirt");
   set_adj("hide");
   add_adj("studded");
   set_short("studded hide shirt");
   set_long("This appears to be a piece of animal hide that has been "
   	+"studded with pieces of bone and obsidian for better protection. "
   	+" It looks to be designed to cover your body, but doesn't look "
   	+"as if it will give you much protection.\n");
   set_ac(25);
   set_at(A_BODY);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,1000);
}


