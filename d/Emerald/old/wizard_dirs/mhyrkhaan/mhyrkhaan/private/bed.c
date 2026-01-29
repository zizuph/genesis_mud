inherit "/std/object.c";
#include "/d/Kalad/defs.h"

void
create_object()
{
   set_name("bed");
   set_adj("plush");
   add_adj("large");
   set_short("large plush bed");
   set_long("This bed is large and soft, you feel you could fall asleep in "+
   "it very easily.\n");
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,500000);
   add_prop(OBJ_I_VALUE,10000);
}
