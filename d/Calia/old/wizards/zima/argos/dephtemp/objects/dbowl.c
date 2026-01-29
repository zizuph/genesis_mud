/* Just a bowl   found on a table in the rooms/dine1. it is dirty.    */
/* when washed in rooms/kitchen it's value increases 5 times          */
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
 
create_object()
{
    set_name(({"bowl",DIRTY_BOWL}));
    set_adj("gold");
    set_short("bowl");
    set_long("@@long_desc");
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 60);
    add_prop(OBJ_I_VALUE,  50);
    add_prop(IS_DIRTY,1);
}
string long_desc() {
   if (this_object()->query_prop(IS_DIRTY)) return
      "It is a beautiful gold bowl, but it is covered with smelly "+
      "dried stew. It might be worth something if it were clean.\n";
   else return
      "It is a beautiful gold bowl, cleaned and polished to a "+
      "bright luster. It looks of value.\n";
}
