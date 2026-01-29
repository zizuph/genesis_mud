inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("mace");
   set_adj("large");
   add_adj("spiked");
   set_long("This is a very large mace crafted from what appears to be "
   	+"the femur of a some large creature lashed to a chunk of obsidian "
   	+"that has irregular spikes sticking out of it at all angles.  "
        +"There is one large beak-like spike protruding out from it, "
        +"which looks as if it could cause grievous wounds.\n");
   set_hit(26);
   set_pen(36);
   set_wt(W_CLUB);
   set_dt(W_IMPALE|W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,4000);
   add_prop(OBJ_I_VOLUME,2000);
}

