
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"


void
create_object()
{
   set_name(({"ornament","_flotsam_r_webnet_"}));
   add_name("webnet");
   set_adj("sparkling");
   add_adj("hair");
   set_long("@@my_long");
   add_prop(OBJ_I_VALUE, 20000);
   add_prop(OBJ_M_NO_SELL,"Hmm... you could probably get a better " +
      "price elsewhere!\n");
}


string
my_long()
{
   return "This delicate and beautiful ornament is " +
   "a hair net as fine as cobweb. It twinkles with tiny " +
   "jewels like the stars. Undoubtably it would be worth a " +
   "fortune in " +
   "any market.\n";
}




