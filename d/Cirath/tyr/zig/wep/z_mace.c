
inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("mace");
   set_adj("spiked");
   add_adj("granite");
   set_long("Large spikes made from the thorns of "
   	+"some desert plant protrude from the sides "
   	+"of a large piece of granite.  You aren't "
   	+"quite sure how they got there, but they "
   	+"look like they would do a lot of damage if "
   	+"they hit you.\n");
   set_hit(20);
   set_pen(45);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_VALUE,1850);
}

