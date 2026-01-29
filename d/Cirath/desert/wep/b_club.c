inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_weapon()
{
   set_name("club");
   set_adj("heavy");
   add_adj("stone");
   set_long("Crafted from a large piece of granite lashed precariously "
   	+"to a wooden haft, this club is not so impressive to look at.  "
   	+"Sometimes looks can be deceiving, though.  This club obviously "
   	+"weighs quite a bit, and the dried, crusty blood covering its "
   	+"massive head makes you quite sure that it has done some damage "
   	+"in the past.\n");
   set_hit(26);
   set_pen(38);
   set_wt(W_CLUB);
   set_dt(W_IMPALE|W_BLUDGEON);
    set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,3000);
}

