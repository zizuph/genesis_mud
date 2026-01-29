inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("club");
   set_adj("heavy");
   add_adj("iron-banded");
   set_long("This large club looks to have been crafted from the "
   	+"root of some sort of tree.  Thick and bulbous, it has "
   	+"thick bands of heavy iron wrapped around it to give it "
   	+"both weight and added force.  It could probably do quite "
   	+"a bit of damage.\n");
   set_hit(37);
   set_pen(37);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,9500);
   add_prop(OBJ_I_VOLUME,5000);
}

