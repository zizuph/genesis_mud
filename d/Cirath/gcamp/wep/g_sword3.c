inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("sword");
   set_adj("blunt-tipped");
   add_adj("iron");
   set_long("Long and blackened with wear, this iron sword looks "
   	+"to have been through many fights.  Its blunt-tip lends "
   	+"it more to slashing than stabbing, and its razor sharp "
   	+"blade looks more than up to that task.\n");
   set_hit(36);
   set_pen(38);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,1500);
}

