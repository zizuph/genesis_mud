inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "../chapel.h"
#include <composite.h>


void
create_object()
{
   set_name("flower");
   add_name("daisy");
   add_adj("common");
   set_long("This is a common daisy, growing among all the other flowers. It is a warm shade of "+
      "yellow. You feel almost child-like again as this flower makes you grin merrily.\n");
   
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 350);
}

