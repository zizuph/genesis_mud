inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("cap");
   set_adj("hide");
   add_adj("spiked");
   set_short("spiked hide cap");
   set_long("Made from the hide of some creature, this cap "
   	+"is set with a number of large bone spikes.  The "
   	+"spikes seem to be covered in dark red stains, "
   	+"you wonder how those got there.\n");
   set_ac(25);
   set_at(A_HEAD);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
}

