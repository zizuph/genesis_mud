inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("shield");
   set_adj("hide");
   add_adj("spiked");
   set_short("spiked hide shield");
   set_long("This medium sized shield is made from "
   	+"the hide of some creature.  It manages to "
   	+"be both strong and light.  Covering the outside "
   	+"of the shield are a number of spikes that are "
   	+"roughly the size of your hand.  Those trained "
   	+"in the use of this item can inflict large amounts "
   	+"of damage with their shield.\n");
   set_ac(20);
   set_at(A_SHIELD);
   add_prop(OBJ_I_VALUE,70);
}

