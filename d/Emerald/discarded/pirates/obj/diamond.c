inherit "/std/object";

#include "defs.h"

void
create_object()
{
   set_short("shimmering diamond");
   set_name("diamond");
   set_adj("shimmering");
   set_long("It is breath-taking. Each facet gives off an array of "+
      "beautiful colours.\n");
   
   add_prop(OBJ_I_VALUE, 100 + random(50));
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
   
   seteuid(getuid());
}


