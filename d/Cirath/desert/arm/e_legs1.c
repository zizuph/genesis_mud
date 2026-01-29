inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../defs.h"

create_armour()
{
   set_name("boots");
   set_adj("tall");
   add_adj("leather");
   set_long("This pair of hardened leather boots are unusually tall.  "
   	+"They reach to just above the knee offering excellent "
   	+"protection to your legs, as well as the ability to wade "
   	+"through deep sand without getting a boot full of sand in "
   	+"the process.  The soft well-worn sole on the bottom makes "
   	+"them extremely comfortable.\n");
   set_ac(22);
    set_at(A_LEGS);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,500);
}

