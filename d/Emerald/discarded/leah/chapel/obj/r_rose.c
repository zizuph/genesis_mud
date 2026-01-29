inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "../chapel.h"
#include <composite.h>


void
create_object()
{
   set_name("rose");
   add_name("flower");
   add_adj("blood-red");
set_long("You are holding a beautiful, newly budding blood-red "+
"rose. Gazing at it brings out the lover in you. \n");
   
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 350);
}

