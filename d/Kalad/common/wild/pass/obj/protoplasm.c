inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
/* by Antharanos */

create_object()
{
   set_short("disgusting heap of protoplasm");
   set_name("protoplasm");
   add_name("disgusting heap");
   add_name("heap");
   set_long("The nasty remnants of some sort of creature, all that is "+
      "visible are plastered bits of some odd flesh\n");
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,50000);
}
