inherit "/std/armour";
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helm");
   set_adj("spiked");
   add_adj("carapace");
   set_short("spiked carapace helm");
   set_long("Created from the shell of some large desert insect, this "
   	+"helm seems to be one of the most protective non-metal helms "
   	+"commonly found in Athas.  In addition to its standard "
   	+"protective use, there are sharpened pieces of bone protruding "
   	+"from it that look as if they could hurt..\n");
   set_ac(20);
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT,1500);
   add_prop(OBJ_I_VOLUME,800);
}

