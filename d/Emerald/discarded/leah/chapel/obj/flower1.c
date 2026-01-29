inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "../chapel.h"
#include <composite.h>


void
create_object()
{
   set_name("flower");
   add_name("star_flower");
   add_adj("star");
   set_long("This is a large star shaped blossom. It is a vibrant hue of "+
      "purple-blue. You feel a smile spread on your face as you look at it.\n");
   
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 350);
}

