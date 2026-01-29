inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("sword");
   set_adj("jagged");
   add_adj("bone");
   set_long("This sword appears to be made from "
   	+"a large bone from some creature.  It has "
   	+"been shaped to accommodate a row of jagged "
   	+"obsidian shards.  It looks to be bound together "
   	+"with some form of leathery straps as well as "
   	+"some form of adhesive.  You think this could "
   	+"really do some damage to someone.\n");
   set_hit(28);
   set_pen(34);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,1954);
}

