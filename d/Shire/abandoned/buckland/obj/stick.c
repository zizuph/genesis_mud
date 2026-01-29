inherit "/std/object";
#include <stdproperties.h>
#include "/sys/macros.h"


void
create_object()
{
   set_name("stick");
   set_pname("sticks");
   set_adj("long");
   set_long("The branch swings back and forth in the wind.\n");
   set_short("stick");
   set_pshort("sticks");
   set_long("A long thin stick. It looks like it's about to fall apart.\n");
   
   add_prop(OBJ_I_VOLUME, 1200);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 400);
}

