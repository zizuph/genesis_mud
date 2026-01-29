inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "../chapel.h"
#include <composite.h>


void
create_object()
{
   set_name("flower");
   add_name("rose");
   add_adj("delicate");
   set_long("This is a delicate budding rose. It is a subtle hue of "+
      "pink. You feel happier as you absorb it's beauty.\n");
   
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 350);
}

