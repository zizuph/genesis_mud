/* Just a goblet found on a table in the rooms/dine1. it is dirty.    */
/* when washed in rooms/kitchen it's value increases 5 times          */
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
 
create_object()
{
    set_name(({"goblet",DIRTY_GOBLET}));
    set_adj("gold");
    set_short("goblet");
    set_long("@@long_desc");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE,  40);
    add_prop(IS_DIRTY,1);
}
string long_desc() {
   if (this_object()->query_prop(IS_DIRTY)) return
      "It is a beautiful gold goblet, but it is stained with wine, "+
      "ruining its value. You wish you could shine it up a bit.\n";
   else return
      "It is a beautiful gold goblet, cleaned and polished to a "+
      "bright luster. It looks of value.\n";
}
